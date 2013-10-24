# $NetBSD$

.include <bsd.own.mk>

TESTSDIR=	${TESTSBASE}/share/mk

TESTS_SH=	t_lib t_own t_prog t_test
.for test in ${TESTS_SH}
TESTS_SH_SRC_${test}=	${test}.sh common.subr
.endfor

.include <bsd.test.mk>
