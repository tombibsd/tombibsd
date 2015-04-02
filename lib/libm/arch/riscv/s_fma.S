/* $NetBSD$ */

/* The contents of this file are in the public domain. */

#include <machine/asm.h>

ENTRY(fma)
	fmadd.d	fa0, fa0, fa1, fa2
	ret
END(fma)
