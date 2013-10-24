#	$NetBSD$
#	from: @(#)Makefile	8.1 (Berkeley) 6/5/93

.include <bsd.own.mk>

PROG=	rtquery
MAN=	rtquery.8
BINDIR?=	/usr/sbin
.if !defined(NOPIC)
LDSTATIC?=
.endif
#COPTS=	-g -DDEBUG -Wall

CWARNFLAGS.clang+=	-Wno-array-bounds

.include "../../Makefile.inc"
.include <bsd.prog.mk>
