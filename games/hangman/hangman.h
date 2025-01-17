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
 *
 *	@(#)hangman.h	8.1 (Berkeley) 5/31/93
 */

#include	<sys/types.h>
#include	<sys/stat.h>
#include	<ctype.h>
#include	<curses.h>
#include	<signal.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	"pathnames.h"

#define	MINLEN	6
#define	MAXERRS	7

#define	MESGY	12
#define	MESGX	0
#define	PROMPTY	11
#define	PROMPTX	0
#define	KNOWNY	10
#define	KNOWNX	1
#define	NUMBERY	4
#define	NUMBERX	(COLS - 1 - 26)
#define	AVGY	5
#define	AVGX	(COLS - 1 - 26)
#define	GUESSY	2
#define	GUESSX	(COLS - 1 - 26)


typedef struct {
	short   y, x;
	char    ch;
}       ERR_POS;

extern bool Guessed[];

extern char Word[], Known[];
extern const char *const Noose_pict[];

extern int Errors, Wordnum;
extern unsigned int Minlen;

extern double Average;

extern const ERR_POS Err_pos[];

extern const char *Dict_name;

extern FILE *Dict;

extern off_t Dict_size;

void    die(int) __dead;
void    endgame(void);
int	main(int, char *[]);
void	getguess(void);
void	getword(void);
void	playgame(void);
void	prdata(void);
void	prman(void);
void	prword(void);
int	readch(void);
void	setup(void);
