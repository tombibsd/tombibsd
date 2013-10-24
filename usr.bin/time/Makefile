#	$NetBSD$
#	@(#)Makefile	8.1 (Berkeley) 6/6/93

.include <bsd.own.mk>

CPPFLAGS+=	-DNOT_CSH
CPPFLAGS+=	-I. -I${NETBSDSRCDIR}/bin
SRCS=	time.c xtime.c
PROG=	time

.PATH: ${NETBSDSRCDIR}/bin/csh

LDADD+=-lutil
DPADD+=${LIBUTIL}

.include <bsd.prog.mk>
