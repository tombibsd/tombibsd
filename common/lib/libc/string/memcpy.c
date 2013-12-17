/*	$NetBSD$	*/

#define MEMCOPY
#include "bcopy.c"

#if defined(__ARM_EABI__)
__strong_alias(__aeabi_memcpy, memcpy)
#endif
