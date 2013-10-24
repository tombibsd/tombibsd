#	$NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/dev/pci

KMOD=	if_alc
IOCONF=	if_alc.ioconf

SRCS=	if_alc.c

CPPFLAGS+=	-DINET -DNVLAN=1

.include <bsd.kmodule.mk>
