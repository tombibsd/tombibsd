# $NetBSD$

USE_FORT?=yes	# network client

PROG=	mld6query
SRCS=	mld6.c
MAN=	mld6query.8

CPPFLAGS+= -DINET6 -DIPSEC

.include <bsd.prog.mk>
