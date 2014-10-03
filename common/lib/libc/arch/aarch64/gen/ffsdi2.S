/* $NetBSD$ */

#include <machine/asm.h>

RCSID("$NetBSD$")

ENTRY(ffsdi2)
	rbit	x1, x0
	clz	x1, x1
	add	x1, x1, #1
	cmp	x0, #0
	csel	w0, wzr, w1, eq
	ret
END(ffsdi2)
