#	$NetBSD$

.include "../Makefile.inc"

.PATH:		${S}/dev/gpio

KMOD=   	gpioiic
IOCONF=		gpioiic.ioconf
SRCS=		gpioiic.c

CPPFLAGS+=	-I${S}/gpio

.include <bsd.kmodule.mk>
