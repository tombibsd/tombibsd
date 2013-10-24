#	$NetBSD$

PROG_CXX=	llvm-prof
NOMAN=		yes

.include <bsd.init.mk>

.PATH: ${LLVM_SRCDIR}/tools/llvm-prof

SRCS=	llvm-prof.cpp

LLVM_LIBS+= \
	BitReader \
	Analysis \
	IR \
	Support

.include "${.PARSEDIR}/../../link.mk"

.include <bsd.prog.mk>
