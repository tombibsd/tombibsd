#	$NetBSD$

USE_FORT?= yes	# network server

PROG=	isibootd
SRCS=	isibootd.c
MAN=	isibootd.8

LDADD+=	-lutil
DPADD+=	${LIBUTIL}

.include <bsd.own.mk>
.include <bsd.prog.mk>
