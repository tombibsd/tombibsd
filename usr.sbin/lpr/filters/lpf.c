/*	$NetBSD$	*/
/*
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#ifndef lint
__COPYRIGHT("@(#) Copyright (c) 1983, 1993\
 The Regents of the University of California.  All rights reserved.");
#if 0
static char sccsid[] = "@(#)lpf.c	8.1 (Berkeley) 6/6/93";
#else
__RCSID("$NetBSD$");
#endif
#endif /* not lint */

/*
 * 	filter which reads the output of nroff and converts lines
 *	with ^H's to overwritten lines.  Thus this works like 'ul'
 *	but is much better: it can handle more than 2 overwrites
 *	and it is written with some style.
 *	modified by kls to use register references instead of arrays
 *	to try to gain a little speed.
 */

#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXWIDTH  132
#define MAXREP    10

static char	buf[MAXREP][MAXWIDTH];
static int	maxcol[MAXREP] = {-1};
static int	lineno;
static int	width = 132;	/* default line length */
static int	length = 66;	/* page length */
static int	indent;		/* indentation length */
static int	npages = 1;
static int	literal;	/* print control characters */
static char	*name;		/* user's login name */
static char	*host;		/* user's machine name */
static char	*acctfile;	/* accounting information file */
static int	crnl;		/* \n -> \r\n */
static int	need_cr;

__dead static void usage(void);

int
main(int argc, char *argv[])
{
	FILE *p = stdin, *o = stdout;
	int i, col;
	char *cp;
	int done, linedone, maxrep, ch, prch;
	char *limit;

        while ((ch = getopt(argc, argv, "cfh:i:j:l:n:w:")) != -1)
		switch (ch) {
		case 'n':
			name = optarg;
			break;
		case 'h':
			host = optarg;
			break;
		case 'w':
			if ((i = atoi(optarg)) > 0 && i <= MAXWIDTH)
				width = i;
			break;
		case 'l':
			length = atoi(optarg);
			break;
		case 'i':
			indent = atoi(optarg);
			break;
		case 'c':	/* Print control chars */
			literal++;
			break;
		case 'f':	/* Fix missing carriage returns */
			crnl++;
			break;
		case 'j':	/* ignore job name */
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;
	if (argc)
		acctfile = *argv;

	memset(buf, ' ',  sizeof(buf));
	done = 0;
	
	while (!done) {
		col = indent;
		maxrep = -1;
		linedone = 0;
		prch = ch = 0;
		need_cr = 0;
		while (!linedone) {
			prch = ch;
			switch (ch = getc(p)) {
			case EOF:
				linedone = done = 1;
				ch = '\n';
				break;

			case '\f':
				lineno = length;
			case '\n':
				if (crnl && prch != '\r')
					need_cr = 1;
				if (maxrep < 0)
					maxrep = 0;
				linedone = 1;
				break;

			case '\b':
				if (--col < indent)
					col = indent;
				break;

			case '\r':
				col = indent;
				break;

			case '\t':
				col = ((col - indent) | 07) + indent + 1;
				break;

			case '\031':
				/*
				 * lpd needs to use a different filter to
				 * print data so stop what we are doing and
				 * wait for lpd to restart us.
				 */
				if ((ch = getchar()) == '\1') {
					fflush(stdout);
					kill(getpid(), SIGSTOP);
					break;
				} else {
					ungetc(ch, stdin);
					ch = '\031';
				}

			default:
				if (col >= width || (!literal && ch < ' ')) {
					col++;
					break;
				}
				cp = &buf[0][col];
				for (i = 0; i < MAXREP; i++) {
					if (i > maxrep)
						maxrep = i;
					if (*cp == ' ') {
						*cp = ch;
						if (col > maxcol[i])
							maxcol[i] = col;
						break;
					}
					cp += MAXWIDTH;
				}
				col++;
				break;
			}
		}

		/* print out lines */
		for (i = 0; i <= maxrep; i++) {
			for (cp = buf[i], limit = cp+maxcol[i]; cp <= limit;) {
				putc(*cp, o);
				*cp++ = ' ';
			}
			if (i < maxrep)
				putc('\r', o);
			else {
				if (need_cr)
					putc('\r', o);
				putc(ch, o);
			}
			if (++lineno >= length) {
				fflush(o);
				npages++;
				lineno = 0;
			}
			maxcol[i] = -1;
		}
	}
	if (lineno) {		/* be sure to end on a page boundary */
		putchar('\f');
		npages++;
	}
	if (name && acctfile && access(acctfile, 02) >= 0 &&
	    freopen(acctfile, "a", stdout) != NULL) {
		printf("%7.2f\t%s:%s\n", (float)npages, host, name);
	}
	exit(0);
}

static void
usage(void)
{
        fprintf(stderr,
	  "usage: lpf [-c] [-f] [-h host] [-i indent] [-l length] [-n name] [-w width] [acctfile]\n");
	exit(1);

}

