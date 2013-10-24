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

#ifdef FLOATX80

flag __gtxf2(floatx80, floatx80);

flag
__gtxf2(floatx80 a, floatx80 b)
{

	/* libgcc1.c says a > b */
	return floatx80_lt(b, a);
}
#endif /* FLOATX80 */
