/*	$NetBSD$	*/

/*
 * IEEE-compatible infinityl.c for big-endian 128-bit format -- public domain.
 */

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD$");
#endif /* LIBC_SCCS and not lint */

#include <math.h>

const union __long_double_u __infinityl =
	{ { 0x7f, 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
