#	$NetBSD$

PROG_CXX=	llvm-ranlib
NOMAN=		yes

.include <bsd.init.mk>

.PATH: ${LLVM_SRCDIR}/tools/llvm-ranlib

SRCS=	llvm-ranlib.cpp

LLVM_LIBS+= \
	Archive \
	BitReader \
	IR \
	Support

.include "${.PARSEDIR}/../../link.mk"

.include <bsd.prog.mk>
