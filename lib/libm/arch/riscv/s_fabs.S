/* $NetBSD$ */

/* The contents of this file are in the public domain. */

#include <machine/asm.h>

ENTRY(fabs)
	fabs.d	fa0, fa0
	ret
END(fabs)
