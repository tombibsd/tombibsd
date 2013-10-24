#	$NetBSD$

WARNS?=	2	# XXX -Wcast-qual issues

PROG=	sdiff
SRCS=	common.c edit.c sdiff.c strtonum.c

LDADD+=	-lutil
DPADD+=	${LIBUTIL}

.include <bsd.prog.mk>
