/*	$NetBSD$ */

#include <sys/cdefs.h>
__KERNEL_RCSID(1, "$NetBSD$");

#if defined(__amd64__)
#include "../../sys/compat/linux32/arch/amd64/linux32_syscalls.c"
#else
const char * const linux32_syscallnames[] = { 0 };
#endif
