#	$NetBSD$

LIB=	LLVMSparcAsmParser

.include <bsd.init.mk>

SPARC_OBJDIR!=	cd ${.CURDIR}/../libLLVMSparcCodeGen && ${PRINTOBJDIR}
CPPFLAGS+=	-I${SPARC_OBJDIR} -I${LLVM_SRCDIR}/lib/Target/Sparc

.PATH: ${LLVM_SRCDIR}/lib/Target/Sparc/AsmParser

SRCS+=	SparcAsmParser.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
