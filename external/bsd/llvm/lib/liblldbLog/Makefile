#	$NetBSD$

LIB=	lldbLog

.include <bsd.init.mk>

.PATH: ${LLDB_SRCDIR}/source

SRCS+=	lldb.cpp \
	lldb-log.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
