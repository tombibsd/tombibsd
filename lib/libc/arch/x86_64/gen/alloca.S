/*	$NetBSD$	*/

#include <machine/asm.h>

#if defined(LIBC_SCCS)
	RCSID("$NetBSD$")
#endif

ENTRY(alloca)
	popq	%rdx
	movq	%rsp,%rcx
	addq	$15,%rdi	/*  round up to 16 bytes */
	andq	$~15,%rdi
	subq	%rdi,%rsp
	movq	%rsp,%rax
	jmp	*%rdx
END(alloca)
