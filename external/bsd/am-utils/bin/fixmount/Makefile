#	$NetBSD$

.include "${.CURDIR}/../Makefile.inc"

PROG=	fixmount

DIST=	${IDIST}/fixmount
.PATH:	${DIST} ${IDIST}/conf/checkmount

SRCS=	fixmount.c checkmount_bsd44.c
MAN+=	fixmount.8

CPPFLAGS+=	-I${DIST}
LDADD+=		-lrpcsvc
DPADD+=		${LIBRPCSVC}

.include <bsd.prog.mk>
