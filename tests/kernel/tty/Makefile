# $NetBSD$

.include <bsd.own.mk>

TESTSDIR=	${TESTSBASE}/kernel/tty

TESTS_C=	t_pr

LDADD+=		-lrumpkern_tty -lrumpvfs -lrump -lrumpuser -lpthread

.include <bsd.test.mk>
