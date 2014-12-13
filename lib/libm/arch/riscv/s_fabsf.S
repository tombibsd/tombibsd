/* $NetBSD$ */

/* The contents of this file are in the public domain. */

#include <machine/asm.h>

ENTRY(fabsf)
	fabs.s	fv0, fa0
	ret
END(fabsf)
