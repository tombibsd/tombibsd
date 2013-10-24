#	$NetBSD$

LIB=	LLVMBitWriter

.include <bsd.init.mk>

.PATH: ${LLVM_SRCDIR}/lib/Bitcode/Writer

SRCS+=	BitWriter.cpp \
	BitcodeWriter.cpp \
	BitcodeWriterPass.cpp \
	ValueEnumerator.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
