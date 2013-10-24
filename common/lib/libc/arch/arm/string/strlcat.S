/* $NetBSD$ */

#include <machine/asm.h>

#ifdef _LIBC
WEAK_ALIAS(strlcat, _strlcat)
#include "namespace.h"
#endif

#if defined(_STANDALONE) && 0	/* arm version is always smaller */
#include "strlcat_naive.S"
#else
#include "strlcat_arm.S"
#endif
