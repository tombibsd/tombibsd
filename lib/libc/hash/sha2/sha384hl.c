/* $NetBSD$ */

/*
 * Derived from code written by Jason R. Thorpe <thorpej@NetBSD.org>,
 * April 29, 1997.
 * Public domain.
 */

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD$");
#endif /* LIBC_SCCS and not lint */

#define	HASH_ALGORITHM	SHA384
#define	HASH_FNPREFIX	SHA384_
#define HASH_INCLUDE	<sys/sha2.h>

#include "../hashhl.c"
