/* $NetBSD$ */

#include <machine/asm.h>

RCSID("$NetBSD$")

ENTRY(ctzdi2)
	rbit	x0, x0
	clz	x0, x0
	ret
END(ctzdi2)
