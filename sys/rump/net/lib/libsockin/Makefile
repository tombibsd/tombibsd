#	$NetBSD$
#

LIB=	rumpnet_sockin

SRCS=	sockin.c
SRCS+=	component.c

CPPFLAGS+= -I${RUMPTOP}/librump/rumpkern

RUMPCOMP_USER=	#defined

.include <bsd.lib.mk>
.include <bsd.klinks.mk>
