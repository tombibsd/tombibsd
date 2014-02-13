/*	$NetBSD$ */

#include <machine/asm.h>

ENTRY_NP(return_one)
	mov	r0, #1
	RET
	.align	0
	.globl	return_one_end
return_one_end:
END(return_one)
