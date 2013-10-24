# $NetBSD$

.include <bsd.own.mk>

TESTSDIR=	${TESTSBASE}/lib/libc/ttyio

TESTS_C+=	t_ptm
TESTS_C+=	t_ttyio

LDADD.t_ttyio+=	-lutil

.include <bsd.test.mk>
