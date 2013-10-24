#	$NetBSD$

.include "../Makefile.inc"

.PATH:		${S}/dev/pci

KMOD=		pwdog
IOCONF=		pwdog.ioconf
SRCS=		pwdog.c

CPPFLAGS+=	-I${S}/pci

.include <bsd.kmodule.mk>

