/*	$NetBSD$	*/

/*
 * J.T. Conklin, December 12, 1994
 * Public Domain
 */

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD$");
#endif /* LIBC_SCCS and not lint */

#if defined(__indr_reference)
__indr_reference(_warnx, warnx)
#else

#include <stdarg.h>

void _vwarnx(const char *, va_list);

void
warnx(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	_vwarnx(eval, fmt, ap);
	va_end(ap);
}

#endif
