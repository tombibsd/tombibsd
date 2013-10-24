# $NetBSD$

USE_FORT?= yes	# network protocol library

.include <bsd.own.mk>
.include <${.CURDIR}/../../Makefile.inc>

.PATH:		${HEIMDIST}/base

LIB=		heimbase

SRCS=			\
	array.c		\
	dict.c		\
	number.c	\
	bool.c		\
	heimbase.c	\
	null.c		\
	string.c

INCSDIR=	/usr/include/krb5
INCS=		heimbase.h

.include <${HEIMBASE}/Makefile.rules.inc>
.include <bsd.lib.mk>
