#	$NetBSD$

.include "../Makefile.inc"

.PATH:		${S}/dev/gpio

KMOD=   	gpio
IOCONF=		gpio.ioconf
SRCS=		gpio.c

CWARNFLAGS+=	-Wno-unused

.include <bsd.kmodule.mk>
