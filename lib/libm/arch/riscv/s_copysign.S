/* $NetBSD$ */

/* The contents of this file are in the public domain. */

#include <machine/asm.h>

ENTRY(copysign)
	fsgnj.d	fv0, fa0, fa1
	ret
END(copysign)
