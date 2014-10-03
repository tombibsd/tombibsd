/* $NetBSD$ */

/* The contents of this file are in the public domain. */

#include <machine/asm.h>

ENTRY(fminf)
	fmin.s	fv0, fa0, fa1
	ret
END(fminf)
