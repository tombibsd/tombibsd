#	@(#)Makefile	8.1 (Berkeley) 6/6/93
#	$NetBSD$

PROG=	error
SRCS=	main.c input.c pi.c subr.c filter.c touch.c

DPADD+=	${LIBUTIL}
LDADD+=	-lutil

.include <bsd.prog.mk>
