# $NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/dev/isa

KMOD=	smsc
IOCONF=	smsc.ioconf
SRCS=	smsc.c

#CPPFLAGS+=-DLMDEBUG

WARNS=	4

.include <bsd.kmodule.mk>
