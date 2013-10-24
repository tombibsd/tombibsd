# $NetBSD$

.include "../Makefile.inc"

LIBISCXX=	yes
LIBISPRIVATE=	yes

LIBDPLIBS+=     lua	${.CURDIR}/../../../../mit/lua/lib/liblua
LIBDPLIBS+=     m	${.CURDIR}/../../../../../lib/libm
