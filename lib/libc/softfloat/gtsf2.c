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

flag __gtsf2(float32, float32);

flag
__gtsf2(float32 a, float32 b)
{

	/* libgcc1.c says a > b */
	return float32_lt(b, a);
}
