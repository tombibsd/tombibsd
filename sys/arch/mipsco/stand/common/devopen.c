/*	$NetBSD$	*/

/*-
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
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
 *
 *	@(#)devopen.c	8.1 (Berkeley) 6/10/93
 */

#include <lib/libsa/stand.h>
#include <lib/libkern/libkern.h>

/*
 * Decode the string 'fname', open the device and return the remaining
 * file name if any.
 */
int
devopen(struct open_file *f, const char *fname, char **file)
	/* file:	 out */
{
	int ctlr = 0, unit = 0, part = 0;
	int c, rc;
	char namebuf[20];
	const char *cp;
	char *ncp;
#if !defined(LIBSA_SINGLE_DEVICE)
	int i;
	struct devsw *dp;
#endif

	cp = fname;
	ncp = namebuf;

	/* expect a string like 'dksd(0,0,0)netbsd' */
	while ((c = *cp) != '\0') {
		if (c == '(') {
			cp++;
			break;
		}
		if (ncp < namebuf + sizeof(namebuf) - 1)
			*ncp++ = c;
		cp++;
	}

	/* get controller number */
	if ((c = *cp) >= '0' && c <= '9') {
		ctlr = c - '0';
		c = *++cp;
	}
	
	if (c == ',') {
		/* get SCSI device number */
		if ((c = *++cp) >= '0' && c <= '9') {
			unit = c - '0';
			c = *++cp;
		}
		
		if (c == ',') {
			/* get partition number */
			if ((c = *++cp) >= '0' && c <= '9') {
				part = c - '0';
				/* dksd(,,8)boot -> dksd(,,) */
				if (part >= 8)
					part = 0;
				c = *++cp;
			}
		}
	}
	if (c != ')')
		return (ENXIO);
	cp++;

	*ncp = '\0';

#ifdef LIBSA_SINGLE_DEVICE
	rc = DEV_OPEN(dp)(f, ctlr, unit, part);
#else /* !LIBSA_SINGLE_DEVICE */
	for (dp = devsw, i = 0; i < ndevs; dp++, i++)
		if (dp->dv_name && strcmp(namebuf, dp->dv_name) == 0)
			goto fnd;
	printf("Unknown device '%s'\nKnown devices are:", namebuf);
	for (dp = devsw, i = 0; i < ndevs; dp++, i++)
		if (dp->dv_name)
			printf(" %s", dp->dv_name);
	printf("\n");
	return (ENXIO);

fnd:
#ifdef BOOTNET
	if (strcmp(namebuf, "tftp") == 0)
		rc = (dp->dv_open)(f, namebuf);
	else
#endif /* BOOTNET */
		rc = (dp->dv_open)(f, ctlr, unit, part);
#endif /* !LIBSA_SINGLE_DEVICE */
	if (rc)
		return (rc);

#ifndef LIBSA_SINGLE_DEVICE
	f->f_dev = dp;
#endif
	if (file && *cp != '\0')
		*file = (char *)cp;	/* XXX */
	return (0);
}
