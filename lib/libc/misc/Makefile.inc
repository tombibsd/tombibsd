#	$NetBSD$
#	@(#)Makefile.inc	8.3 (Berkeley) 10/24/94

.PATH: ${ARCHDIR}/misc ${.CURDIR}/misc

# constructor
SRCS+=	initfini.c

# for -fstack-protector
SRCS+=	stack_protector.c
