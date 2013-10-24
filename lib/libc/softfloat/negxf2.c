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

floatx80 __negxf2(floatx80);

floatx80
__negxf2(floatx80 a)
{

	/* libgcc1.c says -a */
	return __mulxf3(a,__floatsixf(-1));
}
#endif /* FLOATX80 */
