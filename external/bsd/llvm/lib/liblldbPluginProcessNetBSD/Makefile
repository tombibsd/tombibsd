#	$NetBSD$

LIB=	lldbPluginProcessNetBSD

.include <bsd.init.mk>

.PATH: ${LLDB_SRCDIR}/source/Plugins/Process/FreeBSD

SRCS+=	ProcessFreeBSD.cpp \
	ProcessMonitor.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
