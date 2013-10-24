#	$NetBSD$

LIB=	LLVMAsmParser

.include <bsd.init.mk>

.PATH: ${LLVM_SRCDIR}/lib/AsmParser

SRCS+=	LLLexer.cpp \
	LLParser.cpp \
	Parser.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
