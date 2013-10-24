# $NetBSD$

NOMAN=		# defined

.include <bsd.own.mk>

TESTSDIR=	${TESTSBASE}/kernel/kqueue/write

TESTS_C=	t_fifo
TESTS_C+=	t_pipe
TESTS_C+=	t_ttypty

LDADD.t_ttypty=	-lutil

.include <bsd.test.mk>
