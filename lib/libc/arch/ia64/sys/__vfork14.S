/* $NetBSD$ */

#include "SYS.h"

SYSCALL(__vfork14)
	/* XXX: watchout for return values for child/parent */ 
	RET
END(__vfork14)	
