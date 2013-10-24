#	$NetBSD$

LIB=	MCLinkerARMCodeGen

.include <bsd.init.mk>

.PATH: ${MCLINKER_SRCDIR}/lib/Target/ARM

SRCS=	ARMDiagnostic.cpp \
	ARMELFDynamic.cpp \
	ARMELFMCLinker.cpp \
	ARMEmulation.cpp \
	ARMGOT.cpp \
	ARMLDBackend.cpp \
	ARMMCLinker.cpp \
	ARMPLT.cpp \
	ARMRelocator.cpp \
	ARMTargetMachine.cpp \
	ARMToARMStub.cpp \
	ARMToTHMStub.cpp \
	THMToARMStub.cpp \
	THMToTHMStub.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
