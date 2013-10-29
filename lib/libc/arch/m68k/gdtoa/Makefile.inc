#	$NetBSD$

SRCS+=	strtof.c

.if ${MACHINE_ARCH} == "m68k"
SRCS+=	strtold_pxL.c
SRCS+=	strtopxL.c
.endif
