#	$NetBSD$

LIB=	lldPasses

.include <bsd.init.mk>

.PATH: ${LLD_SRCDIR}/lib/Passes

SRCS+=	LayoutPass.cpp \
	RoundTripNativePass.cpp \
	RoundTripYAMLPass.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
