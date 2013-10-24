/*	$NetBSD$ */

#include <machine/asm.h>

RCSID("$NetBSD$");

_ENTRY(return_one)
	movq	$0x1, %rax
	retq
LABEL(return_one_end)
