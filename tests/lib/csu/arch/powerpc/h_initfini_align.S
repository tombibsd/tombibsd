/*	$NetBSD$	*/

#include <machine/asm.h>

RCSID("$NetBSD$")

/*
 * LINTSTUB: bool check_stack_alignment(void);
 */

_ENTRY(check_stack_alignment)
	li	%r3,0
	andis.	%r0,%r1,15
	bnelr	%cr0
	li	%r3,1
	blr
END(check_stack_alignment)
