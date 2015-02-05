#	$NetBSD$

LIB=	LLVMExecutionEngine

.include <bsd.init.mk>

.PATH: ${LLVM_SRCDIR}/lib/ExecutionEngine

SRCS+=	GDBRegistrationListener.cpp \
	ExecutionEngine.cpp \
	ExecutionEngineBindings.cpp \
	RTDyldMemoryManager.cpp \
	TargetSelect.cpp

.include <bsd.lib.mk>
