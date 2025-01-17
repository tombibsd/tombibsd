/* $NetBSD$ */
/*-
 * Copyright (c) 1998, 2000 Ben Harris
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
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * intr.h - Interrupt stuff for the consumption of MI code.
 *
 * arm26-specific functions are in irq.h
 */

#ifndef _ARM26_INTR_H_
#define _ARM26_INTR_H_

/*
 * These are the different SPL states
 *
 * Each state has an interrupt mask associated with it which
 * indicate which interrupts are allowed.
 */

#define IPL_NONE	0
#define IPL_SOFTCLOCK	1
#define IPL_SOFTNET	2
#define IPL_SOFTBIO	IPL_SOFTNET
#define IPL_SOFTSERIAL	IPL_SOFTNET
#define IPL_VM		3
#define IPL_SCHED	4
#define IPL_HIGH	4
#define NIPL		IPL_HIGH + 1

#if defined(_KERNEL) && !defined(_LOCORE)

#define splsoftnet()	raisespl(IPL_SOFTNET)
#define splsoftbio()	splsoftnet()
#define splsoftserial()	splsoftnet()
#define splsoftclock()	raisespl(IPL_SOFTCLOCK)
#define splvm()		raisespl(IPL_VM)
#define	splsched()	splhigh()

#define spl0()			lowerspl(IPL_NONE)
#define splx(s)			lowerspl(s)

extern int splhigh(void);
extern int raisespl(int);
extern void lowerspl(int);
extern int hardsplx(int);

typedef uint8_t ipl_t;
typedef struct {
	ipl_t _ipl;
} ipl_cookie_t;

static inline ipl_cookie_t
makeiplcookie(ipl_t ipl)
{

	return (ipl_cookie_t){._ipl = ipl};
}

static inline int
splraiseipl(ipl_cookie_t icookie)
{
	ipl_t newipl = icookie._ipl;

	return ((newipl) == IPL_HIGH) ? splhigh() : raisespl(newipl);
}

/*
 * Interrupt sharing types
 * (not currently used on arm26)
 */

#define	IST_UNUSABLE	-1	/* interrupt cannot be used */
#define	IST_NONE	0	/* none (dummy) */
#define	IST_PULSE	1	/* pulsed */
#define	IST_EDGE	2	/* edge-triggered */
#define	IST_LEVEL	3	/* level-triggered */

#endif /* _KERNEL && !ASSEMBLER */
#endif
