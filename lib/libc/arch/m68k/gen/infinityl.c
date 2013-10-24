/*	$NetBSD$	*/

/*
 * IEEE-compatible infinityl.c for Motorola 68k 80-bit format -- public domain.
 * Note that the representation includes 16 bits of padding between exponent
 * and mantissa.
 */

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD$");
#endif /* LIBC_SCCS and not lint */

#include <math.h>

const union __long_double_u __infinityl =
	{ { 0x7f, 0xff, 0, 0, 0x80, 0, 0, 0, 0, 0, 0, 0 } };
