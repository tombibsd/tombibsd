#	$NetBSD$

LIB=	LLVMIRReader

.include <bsd.init.mk>

.PATH: ${LLVM_SRCDIR}/lib/IRReader

SRCS+=	IRReader.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
