/*	$NetBSD$	*/

/*
 * Written by J.T. Conklin, Apr 4, 1995
 * Public domain.
 */

#include <machine/asm.h>

#ifdef WEAK_ALIAS
WEAK_ALIAS(fpgetprec, _fpgetprec)
ENTRY(_fpgetprec)
#else
ENTRY(fpgetprec)
#endif
	subl $4,%esp
	fnstcw (%esp)
	movl (%esp),%eax
	rorl $8,%eax
	andl $3,%eax
	addl $4,%esp
	ret
