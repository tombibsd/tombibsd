#	$NetBSD$

LIB=	LLVMX86Utils

.include <bsd.init.mk>

.PATH: ${LLVM_SRCDIR}/lib/Target/X86/Utils

SRCS+=	X86ShuffleDecode.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
