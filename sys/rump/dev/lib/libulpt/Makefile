#	$NetBSD$
#

.PATH:	${.CURDIR}/../../../../dev/usb

LIB=	rumpdev_ulpt
IOCONF=	ULPT.ioconf

SRCS=	ulpt.c

SRCS+=	ulpt_at_usb.c

CPPFLAGS+=	-I${RUMPTOP}/librump/rumpvfs

.include <bsd.lib.mk>
.include <bsd.klinks.mk>
