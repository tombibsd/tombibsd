/*	$NetBSD$	*/

/*
 * Written by J.T. Conklin <jtc@NetBSD.org>.
 * Public domain.
 */

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD$");
#endif

#include <sys/types.h>

#undef htons

uint16_t
htons(uint16_t x)
{
#if BYTE_ORDER == LITTLE_ENDIAN
	u_char *s = (void *) &x;
	return (uint16_t)(s[0] << 8 | s[1]);
#else
	return x;
#endif
}
