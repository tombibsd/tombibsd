#	$NetBSD$

.if ${PPC_ARCH_MODE} == "ppc64bridge"
AOPTS+=	-Wa,-mppc64bridge
.endif

CFLAGS+=	-Wa,-maltivec
AFLAGS+=	${AOPTS}
