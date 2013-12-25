/*	$NetBSD$	*/

#include <machine/asm.h>

RCSID("$NetBSD$")

_ENTRY(check_stack_alignment)
	and	%sp, 7, %o1
	retl
	 not	%o1, %o0
