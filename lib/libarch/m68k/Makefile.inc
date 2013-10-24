# $NetBSD$

.if (${MACHINE_ARCH} == "m68k" || ${MACHINE_ARCH} == "m68000")
NOLINT=		# defined
SRCS=		m68k_sync_icache.S
.endif

MAN+=		m68k_sync_icache.2
