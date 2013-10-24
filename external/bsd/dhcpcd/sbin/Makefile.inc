# $NetBSD$

.include <bsd.own.mk>

WARNS?=		4
BINDIR=		/sbin

.if (${MKDYNAMICROOT} == "no")
LDSTATIC?=	-static
.endif

