/* $NetBSD$ */

/*
 * Written by Ben Harris, 2000.  This file is in the Public Domain.
 */

#include "softfloat-for-gcc.h"
#include "milieu.h"
#include "softfloat.h"

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD$");
#endif /* LIBC_SCCS and not lint */

int __aeabi_dcmpgt(float64, float64);

int
__aeabi_dcmpgt(float64 a, float64 b)
{

	return !float64_le(a, b) && float64_eq(a, a) && float64_eq(b, b);
}
