#	$NetBSD$

LIBISPRIVATE=	yes

.include "${.CURDIR}/../../Makefile.inc"

LIB=	diff

DIST=	${IDIST}/${LIB}
.PATH:	${DIST}

SRCS !=	(cd ${DIST} && echo *.c)

CWARNFLAGS.clang+=	-Wno-string-plus-int

.include <bsd.lib.mk>
