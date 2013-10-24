/*	$NetBSD$	*/

#if defined ARM
#include "../../../../arm/include/int_limits.h"
#elif defined MIPS
#include "../../../../mips/include/int_limits.h"
#elif defined SHx
#include "../../../../sh3/include/int_limits.h"
#else
#error "unknown architecture"
#endif
