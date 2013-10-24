# $NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/dev/pci

KMOD=   azalia
IOCONF=	azalia.ioconf

SRCS=	azalia.c
SRCS+=	azalia_codec.c

.include <bsd.kmodule.mk>
