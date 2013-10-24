# $NetBSD$

NOMAN=	# defined

.include <bsd.own.mk>

PROG=	rtsol
SRCS=	rtsold.c rtsol.c if.c probe.c rtsock.c

CPPFLAGS+=-DSMALL -DUSE_RTSOCK

#MAN=	rtsold.8

.PATH:	${NETBSDSRCDIR}/usr.sbin/rtsold

LDADD+=	-lutil
DPADD+=	${LIBUTIL}

.include <bsd.prog.mk>
