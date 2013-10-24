# $NetBSD$

NOMAN=		# defined

.include <bsd.own.mk>

.PATH: ${.CURDIR}/..
TESTSDIR=	${TESTSBASE}/lib/libposix/posix1

DPADD+=		${LIBPOSIX}
LDADD+=		-lposix

TESTS_C=	t_rename

.include <bsd.test.mk>
