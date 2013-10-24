#	$NetBSD$

LIB=	clangASTMatchersDynamic

.include <bsd.init.mk>

.PATH: ${CLANG_SRCDIR}/lib/ASTMatchers/Dynamic

SRCS+=	Diagnostics.cpp \
	Parser.cpp \
	Registry.cpp \
	VariantValue.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
