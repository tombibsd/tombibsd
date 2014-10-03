#	$NetBSD$

HOSTPROGNAME=	nbgpt
HOST_SRCDIR=	sbin/gpt
HOST_CPPFLAGS+=	-I${.CURDIR}

HOST_SRCS+= opendisk.c dehumanize_number.c

NOMAN=	# defined
.PATH.c: ${.CURDIR}/../../lib/libutil ${.CURDIR}/../../lib/libc/gen

.include "${.CURDIR}/../Makefile.nbincludes"
.include "${.CURDIR}/../Makefile.host"
