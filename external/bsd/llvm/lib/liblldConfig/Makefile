#	$NetBSD$

LIB=	lldConfig

.include <bsd.init.mk>

.PATH: ${LLD_SRCDIR}/lib/Config

SRCS+=	Version.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
