/*	$NetBSD$	*/

#include <machine/asm.h>

#if defined(LIBC_SCCS)
__RCSID("$NetBSD$")
#endif

ENTRY(fabs)
	fabs %f1,%f1
	blr
END(fabs)
