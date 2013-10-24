#	$NetBSD$
#

LIB=	rumpnet_shmif

SRCS=	if_shmem.c shmif_busops.c
SRCS+=	component.c

CPPFLAGS+=	-I${.CURDIR}/../../../librump/rumpkern

RUMPCOMP_USER=	# filewatch

.include <bsd.lib.mk>
.include <bsd.klinks.mk>
