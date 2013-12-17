#	$NetBSD$

.include "../Makefile.inc"

.PATH: ${DIST}/pppdump ${NETBSDSRCDIR}/sys/net

PROG=	pppdump
SRCS=	pppdump.c deflate.c bsd-comp.c zlib.c
MAN=	pppdump.8

CPPFLAGS+=	-I${NETBSDSRCDIR}/sys/net -I${.CURDIR}
CPPFLAGS+=	-DDO_BSD_COMPRESS -DDO_DEFLATE

.include <bsd.prog.mk>
