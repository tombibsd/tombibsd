/* $NetBSD$ */

#include <arm/cdefs.h>		/* for _ARM_ARCH_T2 */

#define	STRNLEN

#if defined(_STANDALONE) || (defined(__thumb__) && !defined(_ARM_ARCH_T2))
#include "strlen_naive.S"
#else
#include "strlen_arm.S"
#endif
