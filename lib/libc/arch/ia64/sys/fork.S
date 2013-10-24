/* $NetBSD$ */
	
#include "SYS.h"

ENTRY(__fork, 0)
	CALLSYS_ERROR(fork)
	/* XXX:	 get return value for child */
	RET
END(__fork)