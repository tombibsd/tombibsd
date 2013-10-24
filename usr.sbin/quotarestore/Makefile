#	$NetBSD$

PROG=	quotarestore
SRCS=	quotarestore.c 
MAN=	quotarestore.8

DPADD=	${LIBQUOTA} ${LIBRPCSVC}
LDADD=	-lquota -lrpcsvc

.include <bsd.prog.mk>
