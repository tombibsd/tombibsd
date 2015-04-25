/* $NetBSD$ */

/* The contents of this file are in the public domain. */

#include <machine/asm.h>

ENTRY(__ieee754_sqrt)
	fsqrt.d	fa0, fa0
	ret
END(__ieee754_sqrt)
