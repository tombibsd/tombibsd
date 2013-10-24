# $NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/external/bsd/drm/dist/bsd-core
.PATH:	${S}/external/bsd/drm/dist/shared-core

KMOD=   r128drm
IOCONF=	r128drm.ioconf

SRCS=	r128_drv.c
SRCS+=	r128_cce.c
SRCS+=	r128_irq.c
SRCS+=	r128_state.c

CPPFLAGS+=	-I${S}/external/bsd/drm/dist/bsd-core \
		-I${S}/external/bsd/drm/dist/shared-core

.include <bsd.kmodule.mk>
