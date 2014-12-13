# $NetBSD$

.if !defined(_POWERPC_MAKEFILE_INC)
_POWERPC_MAKEFILE_INC=	yes

.if !defined(RUMPKERNEL)
CFLAGS+= ${${ACTIVE_CC} == "gcc":? -msoft-float :}
.endif

.endif
