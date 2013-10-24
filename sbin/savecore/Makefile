#	$NetBSD$
#	@(#)Makefile	8.2 (Berkeley) 4/17/94

PROG=	savecore
SRCS=	savecore.c zopen.c

MAN=	savecore.8

LDADD=	-lkvm -lutil -lz
DPADD=	${LIBKVM} ${LIBUTIL} ${LIBZ}

.include <bsd.prog.mk>
