#	$NetBSD$

LIB=	lldbHostNetBSD

.include <bsd.init.mk>

.PATH: ${LLDB_SRCDIR}/source/Host/freebsd

SRCS+=	Host.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
