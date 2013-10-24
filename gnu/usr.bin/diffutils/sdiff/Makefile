#	$NetBSD$

.include "${.CURDIR}/../Makefile.inc"

DIST=		${IDIST}/src
.PATH:		${DIST} ${IDIST}/man

PROG=		sdiff
SRCS=		sdiff.c version.c

DPADD+=		${LIBDIFFUTILS}
LDADD+=		${LIBDIFFUTILS}

.include <bsd.prog.mk>
