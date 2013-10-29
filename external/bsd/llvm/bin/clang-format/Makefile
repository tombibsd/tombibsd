#	$NetBSD$

PROG_CXX=	clang-format
NOMAN=		yes

.include <bsd.init.mk>

.PATH: ${CLANG_SRCDIR}/tools/clang-format

SRCS=	ClangFormat.cpp

CLANG_LIBS+= \
	clangFormat \
	clangTooling \
	clangFrontend \
	clangSerialization \
	clangDriver \
	clangParse \
	clangRewriteFrontend \
	clangRewriteCore \
	clangSema \
	clangEdit \
	clangAnalysis \
	clangAST \
	clangLex \
	clangBasic

LLVM_LIBS+= \
	BitReader \
	MCParser \
	MC \
	Option \
	Support

.include "${.PARSEDIR}/../../link.mk"

.include <bsd.prog.mk>
