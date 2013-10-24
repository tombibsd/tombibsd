#	from: @(#)Makefile	8.1 (Berkeley) 6/6/93
#	$NetBSD$

.if ${MACHINE_ARCH} == "alpha" || ${MACHINE_ARCH} == "i386"
PROG=	bad144
.endif
DPADD+= ${LIBUTIL}
LDADD+= -lutil

MAN=	bad144.8

.include <bsd.prog.mk>
