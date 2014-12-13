/*	$NetBSD$	*/
/*
 * Written by Frank van der Linden (fvdl@wasabisystems.com)
 * Public domain.
 */

#include <machine/asm.h>

#if defined(LIBC_SCCS)
RCSID("$NetBSD$")
#endif

ENTRY(div)
	movl	%edi, %eax
	cltd
	idivl	%esi
	salq	$32, %rdx
	orq	%rdx,%rax
	ret
END(div)
