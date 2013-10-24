/*	$NetBSD$	*/

#include <machine/asm.h>

RCSID("$NetBSD$")

_ENTRY(check_stack_alignment)
	movl	%esp, %eax
	andl	$15, %eax
	subl	$8, %eax
	sete	%al
	movzbl	%al, %eax
	ret
