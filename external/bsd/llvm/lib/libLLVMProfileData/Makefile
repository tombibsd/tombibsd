#	$NetBSD$

LIB=	LLVMProfileData

.include <bsd.init.mk>

.PATH: ${LLVM_SRCDIR}/lib/ProfileData

SRCS+=	InstrProf.cpp \
	InstrProfReader.cpp \
	InstrProfWriter.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
