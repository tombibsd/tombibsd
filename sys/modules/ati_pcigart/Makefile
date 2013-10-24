# $NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/external/bsd/drm/dist/bsd-core

KMOD=   ati_pcigart

SRCS=	ati_pcigart.c

CPPFLAGS+=	-I${S}/external/bsd/drm/dist/shared-core

.include <bsd.kmodule.mk>
