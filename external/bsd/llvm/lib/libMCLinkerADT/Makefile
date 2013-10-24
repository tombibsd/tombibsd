#	$NetBSD$

LIB=	MCLinkerADT

.include <bsd.init.mk>

.PATH: ${MCLINKER_SRCDIR}/lib/ADT

SRCS=	StringEntry.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
