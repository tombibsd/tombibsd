/* $NetBSD$ */

#include <machine/asm.h>

ENTRY_NP(return_one)
	mov	x0, #1
	ret
	.globl	return_one_end
return_one_end:
END(return_one)
