#	$NetBSD$

.include <bsd.own.mk>

LIBRCSDIR!=cd $(.CURDIR)/../lib && ${PRINTOBJDIR}
LIBRCS=${LIBRCSDIR}/librcs.a
CPPFLAGS+=-I${.CURDIR}/../lib
LDADD=	${LIBRCS}
DPADD=	${LIBRCS}

.if exists(${.CURDIR}/../../Makefile.inc)
.include "${.CURDIR}/../../Makefile.inc"
.endif
