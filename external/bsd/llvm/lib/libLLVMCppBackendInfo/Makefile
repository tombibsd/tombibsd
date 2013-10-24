#	$NetBSD$

LIB=	LLVMCppBackendInfo

CPPFLAGS+=	-I${LLVM_SRCDIR}/lib/Target/CppBackend

.include <bsd.init.mk>

.PATH: ${LLVM_SRCDIR}/lib/Target/CppBackend/TargetInfo

SRCS+=	CppBackendTargetInfo.cpp

.include <bsd.lib.mk>
