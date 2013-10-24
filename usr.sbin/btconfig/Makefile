# $NetBSD$

USE_FORT?= yes	#network client

PROG=		btconfig
SRCS=		btconfig.c
MAN=		btconfig.8

DPADD+=		${LIBBLUETOOTH} ${LIBUTIL}
LDADD+=		-lbluetooth -lutil

.include <bsd.prog.mk>
