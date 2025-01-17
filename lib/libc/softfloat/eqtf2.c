/* $NetBSD$ */

/*
 * Written by Matt Thomas, 2011.  This file is in the Public Domain.
 */

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD$");
#endif /* LIBC_SCCS and not lint */

#include "softfloat-for-gcc.h"
#include "milieu.h"
#include "softfloat.h"

#ifdef FLOAT128
flag __eqtf2(float128, float128);

flag
__eqtf2(float128 a, float128 b)
{

	/* libgcc1.c says !(a == b) */
	return !float128_eq(a, b);
}
#endif /* FLOAT128 */
