#	$NetBSD$

# objects built from assembler sources (need lint stubs)
# hton* and nto* functions provided by ../gen/byte_swap_*.S
SRCS+=  

LSRCS.mips.net=	Lint_htonl.c Lint_htons.c Lint_ntohl.c Lint_ntohs.c
LSRCS+=		${LSRCS.mips.net}
DPSRCS+=	${LSRCS.mips.net}
CLEANFILES+=	${LSRCS.mips.net}
