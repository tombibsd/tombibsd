/*	$NetBSD$	*/

/*
 * J.T. Conklin, December 12, 1994
 * Public Domain
 */

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD$");
#endif /* LIBC_SCCS and not lint */

#include <stdarg.h>

#if defined(__indr_reference)
__indr_reference(_vwarn, vwarn)
#else

void _vwarn(const char *, va_list);

void
vwarn(const char *fmt, va_list ap)
{
	_vwarn(fmt, ap);
}

#endif
