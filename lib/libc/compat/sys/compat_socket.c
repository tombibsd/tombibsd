/* $NetBSD$ */

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD$");
#endif /* LIBC_SCCS and not lint */

#define __LIBC12_SOURCE__

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <compat/sys/socket.h>

__warn_references(socket,
    "warning: reference to compatibility socket(); include <sys/socket.h> for correct reference")

int
socket(int domain, int type, int protocol)
{
	int res;

	res = __socket30(domain, type, protocol);
	if (errno == EAFNOSUPPORT)
		errno = EPROTONOSUPPORT;
	return res;
}
