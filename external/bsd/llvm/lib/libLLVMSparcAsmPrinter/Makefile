#	$NetBSD$

LIB=	LLVMSparcAsmPrinter

.include <bsd.init.mk>

.PATH: ${LLVM_SRCDIR}/lib/Target/Sparc/InstPrinter

SPARC_OBJDIR!=	cd ${.CURDIR}/../libLLVMSparcCodeGen && ${PRINTOBJDIR}
CPPFLAGS+=	-I${SPARC_OBJDIR} -I${LLVM_SRCDIR}/lib/Target/Sparc

SRCS+=	SparcInstPrinter.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
