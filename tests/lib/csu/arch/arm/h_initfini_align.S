/*	$NetBSD$	*/

#include <machine/asm.h>

RCSID("$NetBSD$")

/*
 * LINTSTUB: bool check_stack_alignment(void);
 */

ARM_ENTRY(check_stack_alignment)
#ifdef __ARM_EABI__
	tst	sp, #7
#else
	tst	sp, #3
#endif
	movne	r0, #0
	moveq	r0, #1
	RET
END(check_stack_alignment)
