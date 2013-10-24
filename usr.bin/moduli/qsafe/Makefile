# $NetBSD$

NOMAN=yes
PROG=   qsafe
SRCS= qsafe.c qfile.c
QSIEVE=${.CURDIR}/../qsieve
.PATH: ${QSIEVE}
CPPFLAGS+=-I${QSIEVE}

.include <bsd.prog.mk>
