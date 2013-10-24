#	$NetBSD$

PROG	= rawwrite.ttp

OBJS	= rawwrite.o
HEADERS	= 

include ../Makefile.inc

${PROG}: ${OBJS} ${LDADD}
	${CC} ${LDFLAGS} -o $@ ${OBJS} ${LDADD} ${LIBS}
