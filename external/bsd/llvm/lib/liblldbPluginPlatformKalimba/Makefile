#	$NetBSD$

LIB=	lldbPluginPlatformKalimba

.include <bsd.init.mk>

.PATH: ${LLDB_SRCDIR}/source/Plugins/Platform/Kalimba

SRCS+=	PlatformKalimba.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
