/*	$NetBSD$	*/

#include <machine/asm.h>

RCSID("$NetBSD$")

LEAF_ENTRY(check_stack_alignment)
	extru	%sp,31,6,%ret0
	comiclr,<> 0, %ret0, %ret0
	ldi	1,%ret0
	bv,n	%r0(%r2)
EXIT(check_stack_alignment)
