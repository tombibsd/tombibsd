/*	$NetBSD$	*/

/*
 * Copyright (c) 1997 Matthew R. Green.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*-
 * Copyright (c) 1980, 1992, 1993
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
#if 0
static char sccsid[] = "@(#)swap.c	8.3 (Berkeley) 4/29/95";
#endif
__RCSID("$NetBSD$");
#endif /* not lint */

#include <sys/param.h>
#include <sys/swap.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "systat.h"
#include "extern.h"

void showspace(char *header, int hlen, long blocksize);

static	long blocksize;
static	int hlen, nswap, rnswap;
static	int first = 1;
static	struct swapent *swap_devices;

WINDOW *
openswap(void)
{

	return (subwin(stdscr, -1, 0, 5, 0));
}

void
closeswap(WINDOW *w)
{

	if (w == NULL)
		return;
	wclear(w);
	wrefresh(w);
	delwin(w);
}

/* do nothing */
int
initswap(void)
{

	return (1);
}

void
fetchswap(void)
{
	int	update_label = 0;

	first = 0;
	nswap = swapctl(SWAP_NSWAP, 0, 0);
	if (nswap < 0)
		error("error: %s", strerror(errno));
	if (nswap == 0)
		return;
	update_label = (nswap != rnswap);

	if (swap_devices)
		(void)free(swap_devices);
	if ((swap_devices = malloc(nswap * sizeof(*swap_devices))) == NULL) {
		error("malloc failed");
		die(0);
	}

	if ((rnswap = swapctl(SWAP_STATS, (void *)swap_devices, nswap)) != nswap) {
		error("swapctl failed");
		die(0);
	}
		
	if (update_label)
		labelswap();
}

void
labelswap(void)
{
	char	*header;
	int	row;

	row = 0;
	wmove(wnd, row, 0);
	wclrtobot(wnd);
	if (first)
		fetchswap();
	if (nswap == 0) {
		mvwprintw(wnd, row++, 0, "No swap");
		return;
	}
	header = getbsize(&hlen, &blocksize);
	mvwprintw(wnd, row++, 0, "%-5s%*s%9s  %55s",
	    "Disk", hlen, header, "Used",
	    "/0%  /10% /20% /30% /40% /50% /60% /70% /80% /90% /100%");
}

void
showswap(void)
{
	int	col, blk_div, i, avail, used, xsize, swp_free;
	struct	swapent *sep;
	char	*p;

	blk_div = blocksize / 512;
	swp_free = avail = 0;
	for (sep = swap_devices, i = 0; i < nswap; i++, sep++) {
		p = strrchr(sep->se_path, '/');
		p = p ? p+1 : sep->se_path;

		mvwprintw(wnd, i + 1, 0, "%-5s", p);

		col = 5;
		mvwprintw(wnd, i + 1, col, "%*d", hlen, sep->se_nblks / blk_div);

		col += hlen;
		xsize = sep->se_nblks;
		used = sep->se_inuse;
		avail += xsize;
		swp_free += xsize - used;
		mvwprintw(wnd, i + 1, col, "%9d  ", used / blk_div);
		wclrtoeol(wnd);
		whline(wnd, 'X', (100 * used / xsize + 1) / 2);
	}
	/* do total if necessary */
	if (nswap > 1) {
		used = avail - swp_free;
		mvwprintw(wnd, i + 1, 0, "%-5s%*d%9d  ",
		    "Total", hlen, avail / blk_div, used / blk_div);
		wclrtoeol(wnd);
		whline(wnd, 'X', (100 * used / avail + 1) / 2);
	}
}
