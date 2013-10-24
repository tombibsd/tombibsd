#	$NetBSD$

# objects built from assembler sources (need lint stubs)
# hton* and nto* functions provided by ../gen/byte_swap_*.S
SRCS+=  

LSRCS.i386.net=	Lint_htonl.c Lint_htons.c Lint_ntohl.c Lint_ntohs.c
LSRCS+=		${LSRCS.i386.net}
DPSRCS+=	${LSRCS.i386.net}
CLEANFILES+=	${LSRCS.i386.net}
