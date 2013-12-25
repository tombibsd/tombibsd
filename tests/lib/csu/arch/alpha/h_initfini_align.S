/*	$NetBSD$	*/

#include <machine/asm.h>

RCSID("$NetBSD$")

/*
 * LINTSTUB: bool check_stack_alignment(void);
 */

LEAF_NOPROFILE(check_stack_alignment, 0)
	ldiq	v0, 0
	and	sp, 7, t0
	cmoveq	t0, 1, v0
	ret
END(check_stack_alignment)
