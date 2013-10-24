#	$NetBSD$

PROG	= chg_pid.ttp

OBJS	= chg_pid.o
HEADERS	=

include ../Makefile.inc

${PROG}: ${OBJS} ${LDADD}
	${CC} ${LDFLAGS} -o $@ ${OBJS} ${LDADD} ${LIBS}
