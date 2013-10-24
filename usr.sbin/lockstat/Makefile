#	$NetBSD$

.include <bsd.own.mk>

SRCS=	elf32.c elf64.c main.c
PROG=	lockstat
MAN=	lockstat.8

DPADD=	${LIBUTIL} 
LDADD=	-lutil

elf64.o:	elf32.c

.include <bsd.prog.mk>
