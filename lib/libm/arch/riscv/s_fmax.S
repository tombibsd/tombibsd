/* $NetBSD$ */

/* The contents of this file are in the public domain. */

#include <machine/asm.h>
#include <machine/math.h>

#ifndef __HAVE_LONG_DOUBLE
STRONG_ALIAS(fmaxl, fmax)
#endif

ENTRY(fmax)
	fmax.d	fv0, fa0, fa1
	ret
END(fmax)
