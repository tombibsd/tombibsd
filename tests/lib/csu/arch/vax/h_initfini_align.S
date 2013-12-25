/*	$NetBSD$	*/

#include <machine/asm.h>

RCSID("$NetBSD$")

/*
 * LINTSTUB: bool check_stack_alignment(void);
 */

_ENTRY(check_stack_alignment, 0)
	clrl	%r0
	bitl	$3,%sp
	bneq	1f
	incl	%r0
1:	ret
END(check_stack_alignment)
