#	$NetBSD$
#

.PATH:	${.CURDIR}/../../../../dev

LIB=	rumpdev_vnd

SRCS=   vnd.c

SRCS+=	vnd_component.c

CPPFLAGS+=	-I${RUMPTOP}/librump/rumpvfs

.include <bsd.lib.mk>
.include <bsd.klinks.mk>
