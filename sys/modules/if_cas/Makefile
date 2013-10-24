#	$NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/dev/pci

KMOD=	if_cas
IOCONF=	if_cas.ioconf
SRCS=	if_cas.c
CPPFLAGS+= -DINET

.include <bsd.kmodule.mk>
