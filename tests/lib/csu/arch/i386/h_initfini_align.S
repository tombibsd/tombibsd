/*	$NetBSD$	*/

#include <machine/asm.h>

RCSID("$NetBSD$")

_ENTRY(check_stack_alignment)
	movl	%esp, %eax
	andl	$3, %eax
	setz	%al
	movzbl	%al, %eax
	ret
