/*	$NetBSD$	*/

 /*
  * tcpdchk - examine all tcpd access control rules and inetd.conf entries
  * 
  * Usage: tcpdchk [-a] [-d] [-i inet_conf] [-v]
  * 
  * -a: complain about implicit "allow" at end of rule.
  * 
  * -d: rules in current directory.
  * 
  * -i: location of inetd.conf file.
  * 
  * -v: show all rules.
  * 
  * Author: Wietse Venema, Eindhoven University of Technology, The Netherlands.
  */

#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#) tcpdchk.c 1.8 97/02/12 02:13:25";
#else
__RCSID("$NetBSD$");
#endif
#endif

/* System libraries. */

#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <syslog.h>
#include <setjmp.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef INADDR_NONE
#define INADDR_NONE     (-1)		/* XXX should be 0xffffffff */
#endif

#ifndef S_ISDIR
#define S_ISDIR(m)	(((m) & S_IFMT) == S_IFDIR)
#endif

/* Application-specific. */

#include "tcpd.h"
#include "inetcf.h"
#include "scaffold.h"

#ifdef NO_NETGRENT
	/* SCO has no *netgrent() support */
#else
# ifdef NETGROUP
#  include <netgroup.h>
# endif
#endif

 /*
  * Stolen from hosts_access.c...
  */
static const char sep[] = ", \t\n";

#define	BUFLEN 2048

int     resident = 0;
int     hosts_access_verbose = 0;
const char *hosts_allow_table = HOSTS_ALLOW;
const char *hosts_deny_table = HOSTS_DENY;
extern jmp_buf tcpd_buf;

 /*
  * Local stuff.
  */
static void usage(void);
static void parse_table(const char *, struct request_info *);
static void print_list(char *, char *);
static void check_daemon_list(char *);
static void check_client_list(char *);
static void check_daemon(char *);
static void check_user(char *);
#ifdef INET6
static int check_inet_addr(char *);
#endif
static int check_host(char *);
static int reserved_name(char *);

int main(int, char **);

#define PERMIT	1
#define DENY	0

#define YES	1
#define	NO	0

static int defl_verdict;
static char *myname;
static int allow_check;
static char *inetcf;

int
main(int argc, char **argv)
{
    struct request_info request;
    struct stat st;
    int     c;

    myname = argv[0];

    /*
     * Parse the JCL.
     */
    while ((c = getopt(argc, argv, "adi:v")) != -1) {
	switch (c) {
	case 'a':
	    allow_check = 1;
	    break;
	case 'd':
	    hosts_allow_table = "hosts.allow";
	    hosts_deny_table = "hosts.deny";
	    break;
	case 'i':
	    inetcf = optarg;
	    break;
	case 'v':
	    hosts_access_verbose++;
	    break;
	default:
	    usage();
	    /* NOTREACHED */
	}
    }
    if (argc != optind)
	usage();

    /*
     * When confusion really strikes...
     */
    if (check_path(REAL_DAEMON_DIR, &st) < 0) {
	tcpd_warn("REAL_DAEMON_DIR %s: %m", REAL_DAEMON_DIR);
    } else if (!S_ISDIR(st.st_mode)) {
	tcpd_warn("REAL_DAEMON_DIR %s is not a directory", REAL_DAEMON_DIR);
    }

    /*
     * Process the inet configuration file (or its moral equivalent). This
     * information is used later to find references in hosts.allow/deny to
     * unwrapped services, and other possible problems.
     */
    inetcf = inet_cfg(inetcf);
    if (hosts_access_verbose)
	printf("Using network configuration file: %s\n", inetcf);

    /*
     * These are not run from inetd but may have built-in access control.
     */
    inet_set("portmap", WR_NOT);
    inet_set("rpcbind", WR_NOT);

    /*
     * Check accessibility of access control files.
     */
    (void) check_path(hosts_allow_table, &st);
    (void) check_path(hosts_deny_table, &st);

    /*
     * Fake up an arbitrary service request.
     */
    request_init(&request,
		 RQ_DAEMON, "daemon_name",
		 RQ_SERVER_NAME, "server_hostname",
		 RQ_SERVER_ADDR, "server_addr",
		 RQ_USER, "user_name",
		 RQ_CLIENT_NAME, "client_hostname",
		 RQ_CLIENT_ADDR, "client_addr",
		 RQ_FILE, 1,
		 0);

    /*
     * Examine all access-control rules.
     */
    defl_verdict = PERMIT;
    parse_table(hosts_allow_table, &request);
    defl_verdict = DENY;
    parse_table(hosts_deny_table, &request);
    return (0);
}

/* usage - explain */

static void
usage(void)
{
    fprintf(stderr, "usage: %s [-a] [-d] [-i inet_conf] [-v]\n", myname);
    fprintf(stderr, "	-a: report rules with implicit \"ALLOW\" at end\n");
    fprintf(stderr, "	-d: use allow/deny files in current directory\n");
    fprintf(stderr, "	-i: location of inetd.conf file\n");
    fprintf(stderr, "	-v: list all rules\n");
    exit(1);
}

/* parse_table - like table_match(), but examines _all_ entries */

static void
parse_table(const char *table, struct request_info *request)
{
    FILE   *fp;
    volatile int     real_verdict;
    char    sv_list[BUFLEN];		/* becomes list of daemons */
    char   *cl_list;			/* becomes list of requests */
    char   *sh_cmd;			/* becomes optional shell command */
    int     verdict;
    volatile struct tcpd_context saved_context;

    saved_context = tcpd_context;		/* stupid compilers */

    if ((fp = fopen(table, "r")) != NULL) {
	tcpd_context.file = table;
	tcpd_context.line = 0;
	while (xgets(sv_list, sizeof(sv_list), fp)) {
	    if (sv_list[strlen(sv_list) - 1] != '\n') {
		tcpd_warn("missing newline or line too long");
		continue;
	    }
	    if (sv_list[0] == '#' || sv_list[strspn(sv_list, " \t\r\n")] == 0)
		continue;
	    if ((cl_list = split_at(sv_list, ':')) == 0) {
		tcpd_warn("missing \":\" separator");
		continue;
	    }
	    sh_cmd = split_at(cl_list, ':');

	    if (hosts_access_verbose)
		printf("\n>>> Rule %s line %d:\n",
		       tcpd_context.file, tcpd_context.line);

	    if (hosts_access_verbose)
		print_list("daemons:  ", sv_list);
	    check_daemon_list(sv_list);

	    if (hosts_access_verbose)
		print_list("clients:  ", cl_list);
	    check_client_list(cl_list);

#ifdef PROCESS_OPTIONS
	    real_verdict = defl_verdict;
	    if (sh_cmd) {
		verdict = setjmp(tcpd_buf);
		if (verdict != 0) {
		    real_verdict = (verdict == AC_PERMIT);
		} else {
		    dry_run = 1;
		    process_options(sh_cmd, request);
		    if (dry_run == 1 && real_verdict && allow_check)
			tcpd_warn("implicit \"allow\" at end of rule");
		}
	    } else if (defl_verdict && allow_check) {
		tcpd_warn("implicit \"allow\" at end of rule");
	    }
	    if (hosts_access_verbose)
		printf("access:   %s\n", real_verdict ? "granted" : "denied");
#else
	    if (sh_cmd)
		shell_cmd(percent_x(buf, sizeof(buf), sh_cmd, request));
	    if (hosts_access_verbose)
		printf("access:   %s\n", defl_verdict ? "granted" : "denied");
#endif
	}
	(void) fclose(fp);
    } else if (errno != ENOENT) {
	tcpd_warn("cannot open %s: %m", table);
    }
    tcpd_context = saved_context;
}

/* print_list - pretty-print a list */

static void print_list(title, list)
char   *title;
char   *list;
{
    char    buf[BUFLEN];
    char   *cp;
    char   *next;

    fputs(title, stdout);
    strlcpy(buf, list, sizeof(buf));

    for (cp = strtok(buf, sep); cp != 0; cp = next) {
	fputs(cp, stdout);
	next = strtok((char *) 0, sep);
	if (next != 0)
	    fputs(" ", stdout);
    }
    fputs("\n", stdout);
}

/* check_daemon_list - criticize daemon list */

static void check_daemon_list(list)
char   *list;
{
    char    buf[BUFLEN];
    char   *cp;
    char   *host;
    int     daemons = 0;

    strlcpy(buf, list, sizeof(buf));

    for (cp = strtok(buf, sep); cp != 0; cp = strtok((char *) 0, sep)) {
	if (STR_EQ(cp, "EXCEPT")) {
	    daemons = 0;
	} else {
	    daemons++;
	    if ((host = split_at(cp + 1, '@')) != 0 && check_host(host) > 1) {
		tcpd_warn("host %s has more than one address", host);
		tcpd_warn("(consider using an address instead)");
	    }
	    check_daemon(cp);
	}
    }
    if (daemons == 0)
	tcpd_warn("daemon list is empty or ends in EXCEPT");
}

/* check_client_list - criticize client list */

static void check_client_list(list)
char   *list;
{
    char    buf[BUFLEN];
    char   *cp;
    char   *host;
    int     clients = 0;
#ifdef INET6
    int l;
#endif

    strlcpy(buf, list, sizeof(buf));

    for (cp = strtok(buf, sep); cp != 0; cp = strtok((char *) 0, sep)) {
#ifdef INET6
	l = strlen(cp);
	if (cp[0] == '[' && cp[l - 1] == ']') {
	    cp[l - 1] = '\0';
	    cp++;
	}
#endif
	if (STR_EQ(cp, "EXCEPT")) {
	    clients = 0;
	} else {
	    clients++;
	    if ((host = split_at(cp + 1, '@')) != NULL) {	/* user@host */
		check_user(cp);
		check_host(host);
	    } else {
		check_host(cp);
	    }
	}
    }
    if (clients == 0)
	tcpd_warn("client list is empty or ends in EXCEPT");
}

/* check_daemon - criticize daemon pattern */

static void check_daemon(pat)
char   *pat;
{
    if (pat[0] == '@') {
	tcpd_warn("%s: daemon name begins with \"@\"", pat);
    } else if (pat[0] == '.') {
	tcpd_warn("%s: daemon name begins with dot", pat);
    } else if (pat[strlen(pat) - 1] == '.') {
	tcpd_warn("%s: daemon name ends in dot", pat);
    } else if (STR_EQ(pat, "ALL") || STR_EQ(pat, unknown)) {
	 /* void */ ;
    } else if (STR_EQ(pat, "FAIL")) {		/* obsolete */
	tcpd_warn("FAIL is no longer recognized");
	tcpd_warn("(use EXCEPT or DENY instead)");
    } else if (reserved_name(pat)) {
	tcpd_warn("%s: daemon name may be reserved word", pat);
    } else {
	switch (inet_get(pat)) {
	case WR_UNKNOWN:
	    tcpd_warn("%s: no such process name in %s", pat, inetcf);
	    inet_set(pat, WR_YES);		/* shut up next time */
	    break;
	case WR_NOT:
	    tcpd_warn("%s: service possibly not wrapped", pat);
	    inet_set(pat, WR_YES);
	    break;
	}
    }
}

/* check_user - criticize user pattern */

static void check_user(pat)
char   *pat;
{
    if (pat[0] == '@') {			/* @netgroup */
	tcpd_warn("%s: user name begins with \"@\"", pat);
    } else if (pat[0] == '.') {
	tcpd_warn("%s: user name begins with dot", pat);
    } else if (pat[strlen(pat) - 1] == '.') {
	tcpd_warn("%s: user name ends in dot", pat);
    } else if (STR_EQ(pat, "ALL") || STR_EQ(pat, unknown)
	       || STR_EQ(pat, "KNOWN")) {
	 /* void */ ;
    } else if (STR_EQ(pat, "FAIL")) {		/* obsolete */
	tcpd_warn("FAIL is no longer recognized");
	tcpd_warn("(use EXCEPT or DENY instead)");
    } else if (reserved_name(pat)) {
	tcpd_warn("%s: user name may be reserved word", pat);
    }
}

#ifdef INET6
static int check_inet_addr(pat)
char	*pat;
{
	struct addrinfo *res;

	res = find_inet_addr(pat, AI_NUMERICHOST);
	if (res) {
		freeaddrinfo(res);
		return 1;
	} else
		return 0;
}
#endif

/* check_host - criticize host pattern */
static int check_host(pat)
char   *pat;
{
    char   *mask;
    int     addr_count = 1;

    if (pat[0] == '@') {			/* @netgroup */
#ifdef NO_NETGRENT
	/* SCO has no *netgrent() support */
#else
#ifdef NETGROUP
	const char   *machinep;
	const char   *userp;
	const char   *domainp;

	setnetgrent(pat + 1);
	if (getnetgrent(&machinep, &userp, &domainp) == 0)
	    tcpd_warn("%s: unknown or empty netgroup", pat + 1);
	endnetgrent();
#else
	tcpd_warn("netgroup support disabled");
#endif
#endif
    } else if ((mask = split_at(pat, '/')) != NULL) {	/* network/netmask */
#ifdef INET6
	char *ep;
#endif
	if (dot_quad_addr(pat, NULL) != INADDR_NONE
	    || dot_quad_addr(mask, NULL) != INADDR_NONE)
	    ; /*okay*/
#ifdef INET6
	else if (check_inet_addr(pat) && check_inet_addr(mask))
	    ; /*okay*/
	else if (check_inet_addr(pat) &&
	    (ep = NULL, strtoul(mask, &ep, 10), ep && !*ep))
	    ; /*okay*/
#endif
	else
	    tcpd_warn("%s/%s: bad net/mask pattern", pat, mask);
    } else if (STR_EQ(pat, "FAIL")) {		/* obsolete */
	tcpd_warn("FAIL is no longer recognized");
	tcpd_warn("(use EXCEPT or DENY instead)");
    } else if (reserved_name(pat)) {		/* other reserved */
	 /* void */ ;
    } else if (NOT_INADDR(pat)) {		/* internet name */
	if (pat[strlen(pat) - 1] == '.') {
	    tcpd_warn("%s: domain or host name ends in dot", pat);
	} else if (pat[0] != '.') {
	    addr_count = check_dns(pat);
	}
    } else {					/* numeric form */
	if (STR_EQ(pat, "0.0.0.0") || STR_EQ(pat, "255.255.255.255")) {
	    /* void */ ;
	} else if (pat[0] == '.') {
	    tcpd_warn("%s: network number begins with dot", pat);
	} else if (pat[strlen(pat) - 1] != '.') {
	    check_dns(pat);
	}
    }
    return (addr_count);
}

/* reserved_name - determine if name is reserved */

static int reserved_name(pat)
char   *pat;
{
    return (STR_EQ(pat, unknown)
	    || STR_EQ(pat, "KNOWN")
	    || STR_EQ(pat, paranoid)
	    || STR_EQ(pat, "ALL")
	    || STR_EQ(pat, "LOCAL"));
}
