# $NetBSD$

.if !defined(RUMPKERNEL)
CFLAGS+=	 -mfloat-abi=soft
.endif
