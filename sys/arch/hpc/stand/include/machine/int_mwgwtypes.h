/*	$NetBSD$	*/

#if defined ARM
#include "../../../../arm/include/int_mwgwtypes.h"
#elif defined MIPS
#include "../../../../mips/include/int_mwgwtypes.h"
#elif defined SHx
#include "../../../../sh3/include/int_mwgwtypes.h"
#else
#error "unknown architecture"
#endif
