/*	$NetBSD$	*/

#if defined ARM
#include "../../../../arm/include/int_const.h"
#elif defined MIPS
#include "../../../../mips/include/int_const.h"
#elif defined SHx
#include "../../../../sh3/include/int_const.h"
#else
#error "unknown architecture"
#endif
