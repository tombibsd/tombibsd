/*	$NetBSD$	*/

#include <sys/cdefs.h>
#ifndef lint
__RCSID("$NetBSD$");
#endif

/*
 * trygetif.c - test program for getif.c
 */

#include <sys/types.h>
#include <sys/socket.h>

#if defined(SUNOS) || defined(SVR4)
#include <sys/sockio.h>
#endif

#include <net/if.h>				/* for struct ifreq */
#include <netinet/in.h>
#include <arpa/inet.h>			/* inet_ntoa */

#include <netdb.h>
#include <stdio.h>
#include <errno.h>

#include "getif.h"

int
main(int argc, char **argv)
{
	struct hostent *hep;
	struct sockaddr ea;			/* Ethernet address */
	struct sockaddr_in *sip;	/* Interface address */
	struct ifreq *ifr;
	struct in_addr dst_addr;
	struct in_addr *dap;
	int i, s;

	dap = NULL;
	if (argc > 1) {
		dap = &dst_addr;
		if (inet_aton(argv[1], &dst_addr) == 0) {
			hep = gethostbyname(argv[1]);
			if (!hep) {
				fprintf(stderr, "gethostbyname(%s)\n", argv[1]);
				exit(1);
			}
			memcpy(&dst_addr, hep->h_addr, sizeof(dst_addr));
		}
	}
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		perror("socket open");
		exit(1);
	}
	ifr = getif(s, dap);
	if (!ifr) {
		fprintf(stderr, "no interface for address\n");
		exit(1);
	}
	printf("Intf-name:%s\n", ifr->ifr_name);
	sip = (struct sockaddr_in *) &(ifr->ifr_addr);
	printf("Intf-addr:%s\n", inet_ntoa(sip->sin_addr));

	return 0;
}
