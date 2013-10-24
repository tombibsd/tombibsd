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

int __aeabi_fcmpge(float32, float32);

int
__aeabi_fcmpge(float32 a, float32 b)
{

	return !float32_lt(a, b) && float32_eq(a, a) && float32_eq(b, b);
}
