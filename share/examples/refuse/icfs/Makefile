# $NetBSD$

PROG=icfs
SRCS=icfs.c virtdir.c
LDADD+= -lrefuse
CPPFLAGS+= -I${.CURDIR}/../virtdir
MAN=icfs.8
WARNS=4

.PATH: ${.CURDIR}/../virtdir

.include <bsd.prog.mk>
