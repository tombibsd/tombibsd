#	$NetBSD$

.include "../Makefile.inc"

.PATH:		${S}/dev/gpio

KMOD=   	gpioow
IOCONF=		gpioow.ioconf
SRCS=		gpioow.c

CPPFLAGS+=	-I${S}/gpio

.include <bsd.kmodule.mk>
