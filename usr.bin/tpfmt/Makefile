#	$NetBSD$

PROG=	tpfmt

CPPFLAGS+= -I${NETBSDSRCDIR}/sys/
SRCS=	tpfmt.c sym.c

LDADD+= -lelf
LDADD+= -lutil
DPADD+= ${LIBELF}
DPADD+= ${LIBUTIL}

.include <bsd.own.mk>
.include <bsd.prog.mk>
