# $NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/dev/ic

KMOD=	apple_smc
SRCS=	apple_smc.c

WARNS=	4

# XXX What's the right thing here?
CPPFLAGS+=	-DDIAGNOSTIC

.include <bsd.kmodule.mk>
