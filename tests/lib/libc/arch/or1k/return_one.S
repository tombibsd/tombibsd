/*	$NetBSD$ */

#include <machine/asm.h>

.globl	return_one, return_one_end

ENTRY_NP(return_one)
	l.addi	r11, r0, 1
	l.jr	lr
	l.nop
return_one_end:
END(return_one)
