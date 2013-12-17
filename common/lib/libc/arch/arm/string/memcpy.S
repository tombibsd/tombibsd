/*	$NetBSD$	*/

#include <arm/cdefs.h>

#if !defined(__XSCALE__) || defined(_STANDALONE)
#include "memcpy_arm.S"
#else
#include "memcpy_xscale.S"
#endif

#if defined(__ARM_EABI__)
STRONG_ALIAS(__aeabi_memcpy, memcpy)
#endif
