#	$NetBSD$
#

.PATH:	${.CURDIR}/../../../../kern

LIB=	rumpkern_time

SRCS+=	kern_time.c
SRCS+=	time_component.c

CPPFLAGS+= -I${RUMPTOP}/librump/rumpkern

.include <bsd.lib.mk>
.include <bsd.klinks.mk>
