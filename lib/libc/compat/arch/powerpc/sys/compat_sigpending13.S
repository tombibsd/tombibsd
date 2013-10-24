/*	$NetBSD$	*/

#include "SYS.h"

#if defined(LIBC_SCCS)
__RCSID("$NetBSD$")
#endif

WARN_REFERENCES(sigpending, \
    "warning: reference to compatibility sigpending(); include <signal.h> for correct reference")

ENTRY(sigpending)
	mr	%r5,%r3				# save pointer
	_DOSYSCALL(compat_13_sigpending13) 	# sigpending()
	bso	1f
	stw	%r3,0(%r5)			# store return value
	li	%r3,0				# and return 0
	blr
1:
	b	_C_LABEL(__cerror)
END(sigpending)
