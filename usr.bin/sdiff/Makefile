#	$NetBSD$

WARNS?=	2	# XXX -Wcast-qual issues

PROG=	sdiff
SRCS=	common.c edit.c sdiff.c
CPPFLAGS+=-D_OPENBSD_SOURCE

LDADD+=	-lutil
DPADD+=	${LIBUTIL}

.include <bsd.prog.mk>
