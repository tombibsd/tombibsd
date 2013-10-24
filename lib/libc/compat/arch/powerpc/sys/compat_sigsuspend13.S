/*	$NetBSD$	*/

#include "SYS.h"

#if defined(LIBC_SCCS)
__RCSID("$NetBSD$")
#endif

WARN_REFERENCES(sigsuspend, \
    "warning: reference to compatibility sigsuspend(); include <signal.h> for correct reference")

ENTRY(sigsuspend)
	lwz	%r3,0(%r3)			# indirect to mask arg
	_DOSYSCALL(compat_13_sigsuspend13)
	b	_C_LABEL(__cerror)		# always terminates with EINTR
END(sigsuspend)
