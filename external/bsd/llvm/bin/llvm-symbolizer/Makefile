#	$NetBSD$

PROG_CXX=	llvm-symbolizer
NOMAN=		yes

.include <bsd.init.mk>

.PATH: ${LLVM_SRCDIR}/tools/llvm-symbolizer

SRCS=	LLVMSymbolize.cpp \
	llvm-symbolizer.cpp

LLVM_LIBS+= \
	DebugInfo \
	Object \
	MCParser \
	MC \
	BitReader \
	IR \
	Support

LDADD+=	-lz
DPADD+=	${LIBZ}

.include "${.PARSEDIR}/../../link.mk"

.include <bsd.prog.mk>
