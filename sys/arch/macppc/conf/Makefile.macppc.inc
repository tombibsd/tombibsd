#	$NetBSD$

.if ${PPC_ARCH_MODE} == "ppc64bridge"
AOPTS+=	${${ACTIVE_CC} == "gcc":? -Wa,-mppc64bridge :}
.endif

AFLAGS+=	${AOPTS}
