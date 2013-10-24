#	$NetBSD$

PROG	= file2swp.ttp

OBJS	= file2swp.o
HEADERS	=
LIBS	= -lxhdi

include ../Makefile.inc

${PROG}: ${OBJS} ${LDADD}
	${CC} -DCOMPRESSED_READ ${LDFLAGS} -o $@ ${OBJS} ${LDADD} ${LIBS}
