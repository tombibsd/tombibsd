#	$NetBSD$

SRCS+=	strtof.c

.if ${MACHINE_ARCH} != "m68000"
SRCS+=	strtold_pxL.c
SRCS+=	strtopxL.c
.endif
