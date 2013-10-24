# $NetBSD$

NOMAN=		# defined 

.include <bsd.own.mk>

TESTSDIR=	${TESTSBASE}/lib/libcrypt

LDADD+=		-lcrypt
DPADD+=		${LIBCRYPT}
WARNS?=		4

TESTS_C=	t_crypt

.include <bsd.test.mk>
