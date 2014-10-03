#	$NetBSD$

LIB=	LLVMMCDisassembler

.include <bsd.init.mk>

.PATH: ${LLVM_SRCDIR}/lib/MC/MCDisassembler

SRCS+=	Disassembler.cpp \
	MCDisassembler.cpp \
	MCExternalSymbolizer.cpp \
	MCRelocationInfo.cpp \

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
