/*	$NetBSD$	*/

#include <machine/asm.h>

RCSID("$NetBSD$")

ENTRY(getstackptr)
	ldr	r0, Lstackptr
	str	r13, [r0]
	mov	pc, r14

Lstackptr:
	.word	_C_LABEL(stackptr)