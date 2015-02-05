#	$NetBSD$

WARNS?=	1	# XXX -Wshadow -Wcast-qual -Wsign-compare
CWARNFLAGS.clang+=	-Wno-tautological-compare

CPPFLAGS+= -D_OPENBSD_SOURCE

.if exists(${.CURDIR}/../../Makefile.inc)
.include "${.CURDIR}/../../Makefile.inc"
.endif

USE_FORT?=yes	# network client *and* setuid
