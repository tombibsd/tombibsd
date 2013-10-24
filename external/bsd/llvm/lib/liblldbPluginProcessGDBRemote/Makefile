#	$NetBSD$

LIB=	lldbPluginProcessGDBRemote

.include <bsd.init.mk>

.PATH: ${LLDB_SRCDIR}/source/Plugins/Process/gdb-remote

SRCS+=	GDBRemoteCommunication.cpp \
	GDBRemoteCommunicationClient.cpp \
	GDBRemoteCommunicationServer.cpp \
	GDBRemoteRegisterContext.cpp \
	ProcessGDBRemote.cpp \
	ProcessGDBRemoteLog.cpp \
	ThreadGDBRemote.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
