/*	$NetBSD$	*/

/*
 * IEEE-compatible infinityf.c -- public domain.
 */

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD$");
#endif /* LIBC_SCCS and not lint */

#include <math.h>
#include <machine/endian.h>

const union __float_u __infinityf =
#if BYTE_ORDER == BIG_ENDIAN
	{ { 0x7f, 0x80,     0,    0 } };
#else
	{ {    0,    0,  0x80, 0x7f } };
#endif
