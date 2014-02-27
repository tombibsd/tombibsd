#	$NetBSD$

LIB=	LLVMLineEditor

.include <bsd.init.mk>

.PATH: ${LLVM_SRCDIR}/lib/LineEditor

SRCS+=	LineEditor.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
