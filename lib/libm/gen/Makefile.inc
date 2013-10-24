#	$NetBSD$

# gen sources
.PATH:	${.CURDIR}/gen
CPPFLAGS+=-I${.CURDIR}/gen

SRCS+=	nan.c nanf.c nanl.c

MAN+=	nan.3

MLINKS+=nan.3 nanf.3 \
	nan.3 nanl.3
