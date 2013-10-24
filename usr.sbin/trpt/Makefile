#	@(#)Makefile	8.1 (Berkeley) 6/6/93
#	$NetBSD$

.include <bsd.own.mk>

USE_FORT?= yes	# network client, effectively

PROG=	trpt
MAN=	trpt.8

DPADD=	${LIBKVM}
LDADD=	-lkvm

.if (${USE_INET6} != "no")
CPPFLAGS+=	-DINET6
.endif

.include <bsd.prog.mk>
