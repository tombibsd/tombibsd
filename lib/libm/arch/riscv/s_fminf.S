/* $NetBSD$ */

/* The contents of this file are in the public domain. */

#include <machine/asm.h>

ENTRY(fminf)
	fmin.s	fa0, fa0, fa1
	ret
END(fminf)
