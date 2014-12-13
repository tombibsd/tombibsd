#	$NetBSD$

LIB=	clangRewrite

.include <bsd.init.mk>

.PATH: ${CLANG_SRCDIR}/lib/Rewrite

SRCS+=	DeltaTree.cpp \
	HTMLRewrite.cpp \
	RewriteRope.cpp \
	Rewriter.cpp \
	TokenRewriter.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
