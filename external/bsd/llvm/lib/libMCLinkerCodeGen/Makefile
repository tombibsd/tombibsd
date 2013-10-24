#	$NetBSD$

LIB=	MCLinkerCodeGen

.include <bsd.init.mk>

.PATH: ${MCLINKER_SRCDIR}/lib/CodeGen

SRCS=	MCLDTargetMachine.cpp \
	MCLinker.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
