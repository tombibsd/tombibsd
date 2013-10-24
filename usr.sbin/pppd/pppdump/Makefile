#	$NetBSD$

.include <bsd.own.mk>

.PATH: ${NETBSDSRCDIR}/dist/pppd/pppdump ${NETBSDSRCDIR}/sys/net

PROG=	pppdump
SRCS=	pppdump.c deflate.c bsd-comp.c zlib.c
MAN=	pppdump.8

CPPFLAGS+=	-I${NETBSDSRCDIR}/sys/net -I${.CURDIR}

.include <bsd.prog.mk>
