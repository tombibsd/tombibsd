/*	$NetBSD$	*/

/*
 * Written by J.T. Conklin <jtc@NetBSD.org>.
 * Public domain.
 */

#include <machine/asm.h>

RCSID("$NetBSD$")

ENTRY(__ieee754_scalb)
	fmoved	%sp@(4),%fp0
	fscaled	%sp@(12),%fp0
#ifndef __SVR4_ABI__
	fmoved	%fp0,%sp@-
	movel	%sp@+,%d0
	movel	%sp@+,%d1
#endif
	rts
