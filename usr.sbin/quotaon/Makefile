#	from: @(#)Makefile	8.1 (Berkeley) 6/6/93
#	$NetBSD$

.include <bsd.own.mk>
WARNS	?= 4

PROG=	quotaon
SRCS=	quotaon.c
MAN=	quotaon.8
MLINKS=	quotaon.8 quotaoff.8
LINKS=	${BINDIR}/quotaon ${BINDIR}/quotaoff

DPADD=	${LIBQUOTA} ${LIBRPCSVC} ${LIBUTIL}
LDADD=	-lquota -lrpcsvc -lutil

.include <bsd.prog.mk>
