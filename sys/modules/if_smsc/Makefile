# $NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/dev/usb

KMOD=	if_smsc
IOCONF=	if_smsc.ioconf
SRCS=	if_smsc.c

WARNS=	4

CPPFLAGS+=	-DINET

.include <bsd.kmodule.mk>
