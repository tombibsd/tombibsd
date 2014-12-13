#	$NetBSD$

LIB=	lldbPluginJITLoaderGDB

.include <bsd.init.mk>

.PATH: ${LLDB_SRCDIR}/source/Plugins/JITLoader/GDB

SRCS+=	JITLoaderGDB.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
