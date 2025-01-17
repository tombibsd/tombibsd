/*	$NetBSD$	*/

/*
 * Copyright (c) 1988, 1993
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
static char sccsid[] = "@(#)tn3270.c	8.2 (Berkeley) 5/30/95";
#else
__RCSID("$NetBSD$");
#endif
#endif /* not lint */

#include <sys/types.h>
#include <sys/time.h>
#include <arpa/telnet.h>
#include <unistd.h>
#include <poll.h>

#include "general.h"
#include "defines.h"
#include "ring.h"
#include "externs.h"

#ifdef TN3270

#include "../ctlr/screen.h"
#include "../ctlr/declare.h"

#include "../ascii/state.h"

#include "../general/globals.h"

#include "../sys_curses/telextrn.h"

int
	HaveInput,		/* There is input available to scan */
	cursesdata,		/* Do we dump curses data? */
	sigiocount;		/* Number of times we got a SIGIO */

char	tline[200];
char	*transcom = 0;	/* transparent mode command (default: none) */

char	Ibuf[8*BUFSIZ], *Ifrontp, *Ibackp;

static char	sb_terminal[] = { IAC, SB,
			TELOPT_TTYPE, TELQUAL_IS,
			'I', 'B', 'M', '-', '3', '2', '7', '8', '-', '2',
			IAC, SE };
#define	SBTERMMODEL	13

static int
	Sent3270TerminalType;	/* Have we said we are a 3270? */

#endif	/* defined(TN3270) */


#ifdef TN3270
void
init_3270(void)
{
    HaveInput = 0;
    sigiocount = 0;
    Sent3270TerminalType = 0;
    Ifrontp = Ibackp = Ibuf;
    init_ctlr();		/* Initialize some things */
    init_keyboard();
    init_screen();
    init_system();
}
#endif	/* defined(TN3270) */


#ifdef TN3270

/*
 * DataToNetwork - queue up some data to go to network.  If "done" is set,
 * then when last byte is queued, we add on an IAC EOR sequence (so,
 * don't call us with "done" until you want that done...)
 *
 * We actually do send all the data to the network buffer, since our
 * only client needs for us to do that.
 */

int
DataToNetwork(char *buffer,	/* where the data is */
    int  count,	/* how much to send */
    int		  done)		/* is this the last of a logical block */
{
    int loop, c;
    int origCount;

    origCount = count;

    while (count) {
	/* If not enough room for EORs, IACs, etc., wait */
	if (NETROOM() < 6) {
	    struct pollfd set[1];

	    set[0].fd = net;
	    set[0].events = POLLOUT;
	    netflush();
	    while (NETROOM() < 6) {
		(void) poll(set, 1, INFTIM);
		netflush();
	    }
	}
	c = ring_empty_count(&netoring);
	if (c > count) {
	    c = count;
	}
	loop = c;
	while (loop) {
	    if (((unsigned char)*buffer) == IAC) {
		break;
	    }
	    buffer++;
	    loop--;
	}
	if ((c = c-loop)) {
	    ring_supply_data(&netoring, buffer-c, c);
	    count -= c;
	}
	if (loop) {
	    NET2ADD(IAC, IAC);
	    count--;
	    buffer++;
	}
    }

    if (done) {
	NET2ADD(IAC, EOR);
	netflush();		/* try to move along as quickly as ... */
    }
    return(origCount - count);
}


void
inputAvailable(int signo)
{
    HaveInput = 1;
    sigiocount++;
}

void
outputPurge(void)
{
    (void) ttyflush(1);
}


/*
 * The following routines are places where the various tn3270
 * routines make calls into telnet.c.
 */

/*
 * DataToTerminal - queue up some data to go to terminal.
 *
 * Note: there are people who call us and depend on our processing
 * *all* the data at one time (thus the poll).
 */

int
DataToTerminal(
    char	*buffer,		/* where the data is */
    int	count)			/* how much to send */
{
    int c;
    int origCount;

    origCount = count;

    while (count) {
	if (TTYROOM() == 0) {
	    struct pollfd set[1];

	    set[0].fd = tout;
	    set[0].events = POLLOUT;
	    (void) ttyflush(0);
	    while (TTYROOM() == 0) {
		(void) poll(set, 1, INFTIM);
		(void) ttyflush(0);
	    }
	}
	c = TTYROOM();
	if (c > count) {
	    c = count;
	}
	ring_supply_data(&ttyoring, buffer, c);
	count -= c;
	buffer += c;
    }
    return(origCount);
}


/*
 * Push3270 - Try to send data along the 3270 output (to screen) direction.
 */

int
Push3270(void)
{
    int save = ring_full_count(&netiring);

    if (save) {
	if (Ifrontp+save > Ibuf+sizeof Ibuf) {
	    if (Ibackp != Ibuf) {
		memmove(Ibuf, Ibackp, Ifrontp-Ibackp);
		Ifrontp -= (Ibackp-Ibuf);
		Ibackp = Ibuf;
	    }
	}
	if (Ifrontp+save < Ibuf+sizeof Ibuf) {
	    (void)telrcv();
	}
    }
    return save != ring_full_count(&netiring);
}


/*
 * Finish3270 - get the last dregs of 3270 data out to the terminal
 *		before quitting.
 */

void
Finish3270(void)
{
    while (Push3270() || !DoTerminalOutput()) {
	HaveInput = 0;
	;
    }
}


/* StringToTerminal - output a null terminated string to the terminal */

void
StringToTerminal(char *s)
{
    int count;

    count = strlen(s);
    if (count) {
	(void) DataToTerminal(s, count);	/* we know it always goes... */
    }
}


/* _putchar - output a single character to the terminal.  This name is so that
 *	curses(3x) can call us to send out data.
 */

int
_putchar(int cc)
{
    char c = (char)cc;
    if (cursesdata) {
	Dump('>', &c, 1);
    }
    if (!TTYROOM()) {
	(void) DataToTerminal(&c, 1);
    } else {
	TTYADD(c);
    }

    return (0);
}

void
SetIn3270(void)
{
    if (Sent3270TerminalType && my_want_state_is_will(TELOPT_BINARY)
		&& my_want_state_is_do(TELOPT_BINARY) && !donebinarytoggle) {
	if (!In3270) {
	    In3270 = 1;
	    Init3270();		/* Initialize 3270 functions */
	    /* initialize terminal key mapping */
	    InitTerminal();	/* Start terminal going */
	    setconnmode(0);
	}
    } else {
	if (In3270) {
	    StopScreen(1);
	    In3270 = 0;
	    Stop3270();		/* Tell 3270 we aren't here anymore */
	    setconnmode(0);
	}
    }
}

/*
 * tn3270_ttype()
 *
 *	Send a response to a terminal type negotiation.
 *
 *	Return '0' if no more responses to send; '1' if a response sent.
 */

int
tn3270_ttype(void)
{
    /*
     * Try to send a 3270 type terminal name.  Decide which one based
     * on the format of our screen, and (in the future) color
     * capaiblities.
     */
    InitTerminal();		/* Sets MaxNumberColumns, MaxNumberLines */
    if ((MaxNumberLines >= 24) && (MaxNumberColumns >= 80)) {
	Sent3270TerminalType = 1;
	if ((MaxNumberLines >= 27) && (MaxNumberColumns >= 132)) {
	    MaxNumberLines = 27;
	    MaxNumberColumns = 132;
	    sb_terminal[SBTERMMODEL] = '5';
	} else if (MaxNumberLines >= 43) {
	    MaxNumberLines = 43;
	    MaxNumberColumns = 80;
	    sb_terminal[SBTERMMODEL] = '4';
	} else if (MaxNumberLines >= 32) {
	    MaxNumberLines = 32;
	    MaxNumberColumns = 80;
	    sb_terminal[SBTERMMODEL] = '3';
	} else {
	    MaxNumberLines = 24;
	    MaxNumberColumns = 80;
	    sb_terminal[SBTERMMODEL] = '2';
	}
	NumberLines = 24;		/* before we start out... */
	NumberColumns = 80;
	ScreenSize = NumberLines*NumberColumns;
	if ((MaxNumberLines*MaxNumberColumns) > MAXSCREENSIZE) {
	    ExitString("Programming error:  MAXSCREENSIZE too small.\n",
								1);
	    /*NOTREACHED*/
	}
	printsub('>', sb_terminal+2, sizeof sb_terminal-2);
	ring_supply_data(&netoring, sb_terminal, sizeof sb_terminal);
	return 1;
    } else {
	return 0;
    }
}

int
settranscom(int argc, char *argv[])
{
	int i;

	if (argc == 1 && transcom) {
	   transcom = 0;
	}
	if (argc == 1) {
	   return 1;
	}
	transcom = tline;
	(void) strlcpy(tline, argv[1], sizeof(tline));
	for (i = 2; i < argc; ++i) {
	    (void) strlcat(tline, " ", sizeof(tline));
	    (void) strlcat(tline, argv[i], sizeof(tline));
	}
	return 1;
}

#endif	/* defined(TN3270) */
