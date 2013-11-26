/*	$NetBSD$	*/

#include <machine/asm.h>

RCSID("$NetBSD$")

_ENTRY(check_stack_alignment)
	add	%sp, BIAS, %o1
	and	%o1, 15, %o2
	retl
	 not	%o2, %o0
