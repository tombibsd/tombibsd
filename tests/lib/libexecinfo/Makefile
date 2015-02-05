# $NetBSD$

.include <bsd.own.mk>

TESTSDIR=	${TESTSBASE}/lib/libexecinfo

TESTS_C+=	t_backtrace
STRIPFLAG=

LDADD+=		-lexecinfo -lelf
DPADD+=		${LIBEXECINFO} ${LIBELF}

COPTS.t_backtrace.c=	-Wno-stack-protector

.include <bsd.test.mk>
