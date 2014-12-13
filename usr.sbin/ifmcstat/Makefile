# $NetBSD$
#	@(#)Makefile	8.1 (Berkeley) 6/5/93

PROG=	ifmcstat
MAN=	ifmcstat.8

LDADD+=	-lutil
DPADD+=	${LIBUTIL}

CPPFLAGS+=	-DINET6

.include <bsd.prog.mk>
