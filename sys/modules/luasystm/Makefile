#	$NetBSD$

.include "../Makefile.inc"

KMOD=		luasystm
SRCS=		luasystm.c

CPPFLAGS+=	-I${S}/../external/mit/lua/dist/src \
		-I${S}/sys

.include <bsd.kmodule.mk>
