#	$NetBSD$

LIB=	clangFrontendTool

.include <bsd.init.mk>

.PATH: ${CLANG_SRCDIR}/lib/FrontendTool

SRCS+=	ExecuteCompilerInvocation.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
