#	$NetBSD$

.include "../Makefile.inc"

KMOD=		luacore
SRCS=		luacore.c

CPPFLAGS+=	-I${S}/../external/mit/lua/dist/src \
		-I${S}/modules/lua

.include <bsd.kmodule.mk>
