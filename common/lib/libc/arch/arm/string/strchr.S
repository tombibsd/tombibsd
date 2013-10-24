/* $NetBSD$ */

#include <machine/asm.h>

STRONG_ALIAS(index, strchr)

#if defined(_STANDALONE) || (defined(__thumb__) && !defined(_ARM_ARCH_T2))
#include "strchr_naive.S"
#else
#include "strchr_arm.S"
#endif
