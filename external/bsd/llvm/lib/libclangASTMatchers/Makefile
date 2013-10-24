#	$NetBSD$

LIB=	clangASTMatchers

.include <bsd.init.mk>

.PATH: ${CLANG_SRCDIR}/lib/ASTMatchers

SRCS+=	ASTMatchFinder.cpp \
	ASTMatchersInternal.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
