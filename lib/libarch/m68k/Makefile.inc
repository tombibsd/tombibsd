# $NetBSD$

.if ${MACHINE_CPU} == "m68k"
NOLINT=		# defined
SRCS=		m68k_sync_icache.S
.endif

MAN+=		m68k_sync_icache.2
