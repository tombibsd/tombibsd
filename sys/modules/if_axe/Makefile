# $NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/dev/usb

KMOD=	if_axe
IOCONF=	if_axe.ioconf
SRCS=	if_axe.c

WARNS=	4

CPPFLAGS+=	-DINET

.include <bsd.kmodule.mk>
