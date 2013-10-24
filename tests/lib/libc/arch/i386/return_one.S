/*	$NetBSD$ */

#include <machine/asm.h>

RCSID("$NetBSD$");

_ENTRY(return_one)
	movl	$0x1,%eax
	ret
LABEL(return_one_end)
