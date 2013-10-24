#	$NetBSD$

PROG=	cdplay
SRCS=	cdplay.c

LDADD+= -ledit -lterminfo -lutil
DPADD+= ${LIBEDIT} ${LIBTERMINFO} ${LIBUTIL}

.include <bsd.prog.mk>
