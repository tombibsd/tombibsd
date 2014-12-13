# $NetBSD$
#
WARNS?=6

.include <bsd.own.mk>

TESTSDIR=	${TESTSBASE}/sys/netinet6
CPPFLAGS+=	-I${NETBSDSRCDIR}/sys -D_TEST

TESTS_C=	t_print

.include <bsd.test.mk>
