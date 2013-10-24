#	$NetBSD$

LIB=	clangEdit

.include <bsd.init.mk>

.PATH: ${CLANG_SRCDIR}/lib/Edit

SRCS+=	Commit.cpp \
	EditedSource.cpp \
	RewriteObjCFoundationAPI.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
