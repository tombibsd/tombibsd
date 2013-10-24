#	$NetBSD$

PROG=	fsck
SRCS=	fsck.c fsutil.c preen.c
MAN=	fsck.8

LDADD+=-lutil
DPADD+=${LIBUTIL}

LDADD+=-lprop
DPADD+=${LIBPROP}

.include <bsd.prog.mk>
