/*	$NetBSD$	*/

/*-
 * Copyright (c) 1985, 1993 The Regents of the University of California.
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
static char sccsid[] = "@(#)acksend.c	8.1 (Berkeley) 6/6/93";
#else
__RCSID("$NetBSD$");
#endif
#endif /* not lint */

#include "globals.h"


struct tsp *answer;

extern u_short sequence;

void
xmit(int type, u_short seq, struct sockaddr_in *addr)
{
	static struct tsp msg;

	msg.tsp_type = type;
	msg.tsp_seq = seq;
	msg.tsp_vers = TSPVERSION;

	set_tsp_name(&msg, hostname);
	bytenetorder(&msg);
	(void)sendtsp(sock, &msg, addr);
}

int
sendtsp(int s, struct tsp *msg, struct sockaddr_in *addr)
{
	int error;

	error = sendto(s, msg, sizeof(*msg), 0,
	    (struct sockaddr *)(void *)addr, sizeof(*addr));
	if (error == -1)
		trace_sendto_err(addr->sin_addr);
	return error;
}


/*
 * Acksend implements reliable datagram transmission by using sequence
 * numbers and retransmission when necessary.
 * If `name' is ANYADDR, this routine implements reliable broadcast.
 *
 * Because this function calls readmsg(), none of its args may be in
 *	a message provided by readmsg().
 */
struct tsp *
acksend(struct tsp *message,		/* this message */
	struct sockaddr_in *addr, char *name,	/* to here */
	int ack,			/* look for this ack */
	struct netinfo *net,		/* receive from this network */
	int bad)			/* 1=losing patience */
{
	struct timeval twait;
	int count;
	long msec;

	message->tsp_vers = TSPVERSION;
	message->tsp_seq = sequence;
	if (trace) {
		fprintf(fd, "acksend: to %s: ",
			(name == ANYADDR ? "broadcast" : name));
		print(message, addr);
	}
	bytenetorder(message);

	msec = 200;
	count = bad ? 1 : 5;	/* 5 packets in 6.4 seconds */
	answer = 0;
	do {
		if (!answer) {
			/* do not go crazy transmitting just because the
			 * other guy cannot keep our sequence numbers
			 * straight.
			 */
			if (sendtsp(sock, message, addr) == -1)
				break;
		}

		mstotvround(&twait, msec);
		answer  = readmsg(ack, name, &twait, net);
		if (answer != 0) {
			if (answer->tsp_seq != sequence) {
				if (trace)
					fprintf(fd,"acksend: seq # %u!=%u\n",
						answer->tsp_seq, sequence);
				continue;
			}
			break;
		}

		msec *= 2;
	} while (--count > 0);
	sequence++;

	return(answer);
}
