#	$NetBSD$

PROG=	swapctl
SRCS=	swapctl.c swaplist.c
MAN=	swapctl.8
LDADD+=	-lutil
DPADD+=	${LIBUTIL}

LINKS=	${BINDIR}/swapctl ${BINDIR}/swapon
MLINKS=	swapctl.8 swapon.8

.include <bsd.prog.mk>
