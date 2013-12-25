/*	$NetBSD$	*/

#include <machine/asm.h>

RCSID("$NetBSD$")

/*
 * LINTSTUB: bool check_stack_alignment(void);
 */

LEAF_NOPROFILE(check_stack_alignment)
#ifdef __mips_o32
	andi	v1,sp,3
#else
	andi	v1,sp,7
#endif
	sltiu	v0,v1,1
	jr	ra
END(check_stack_alignment)
