#	$NetBSD$
#

.PATH:	${.CURDIR}/../../../../dev/pud

LIB=	rumpdev_pud

SRCS=	pud.c pud_dev.c

SRCS+=	component.c

CPPFLAGS+=	-I${RUMPTOP}/librump/rumpvfs

.include <bsd.lib.mk>
.include <bsd.klinks.mk>
