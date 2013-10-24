#	$NetBSD$

.include <bsd.own.mk>

PROG=	pvctxctl
MAN=	pvctxctl.8

.if (${USE_INET6} != "no")
CPPFLAGS+=-DINET6
.endif

.include <bsd.prog.mk>
