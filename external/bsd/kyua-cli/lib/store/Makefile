# $NetBSD$

KYUA_LIBS=	utils

.include <bsd.init.mk>

.PATH:		${SRCDIR}/store

LIB=		store

WARNS?=		3

SRCS=		backend.cpp \
		dbtypes.cpp \
		exceptions.cpp \
		metadata.cpp \
		transaction.cpp

.include <bsd.lib.mk>
