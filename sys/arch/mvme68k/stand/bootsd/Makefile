#	from: @(#)Makefile	8.1 (Berkeley) 6/10/93
#	$NetBSD$

SRCS=   boot.c conf.c
PROG=	bootsd 
LIBS=	${LIBSA} ${LIBKERN} ${LIBBUG}
DPADD=	${LIBS}

.include "../Makefile.booters"

.include <bsd.prog.mk>
