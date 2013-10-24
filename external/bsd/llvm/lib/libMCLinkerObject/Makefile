#	$NetBSD$

LIB=	MCLinkerObject

.include <bsd.init.mk>

.PATH: ${MCLINKER_SRCDIR}/lib/Object

SRCS=	ObjectBuilder.cpp \
	ObjectLinker.cpp \
	SectionMap.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
