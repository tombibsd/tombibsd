# $NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/dev/usb

KMOD=	if_axen
IOCONF=	if_axen.ioconf
SRCS=	if_axen.c

WARNS=	4

CPPFLAGS+=	-DINET

.include <bsd.kmodule.mk>
