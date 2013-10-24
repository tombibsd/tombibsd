/*	$NetBSD$	*/

#if defined ARM
#include "../../../../arm/include/int_types.h"
#elif defined MIPS
#include "../../../../mips/include/int_types.h"
#elif defined SHx
#include "../../../../sh3/include/int_types.h"
#else
#error "unknown architecture"
#endif
