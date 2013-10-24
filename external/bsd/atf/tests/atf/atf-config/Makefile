# $NetBSD$

.include <bsd.own.mk>

TESTSDIR=	${TESTSBASE}/atf/atf-config
ATFFILE=	yes

SRCDIR=		${NETBSDSRCDIR}/external/bsd/atf/dist
.PATH:		${SRCDIR}/atf-config

CPPFLAGS+=	-DHAVE_CONFIG_H

TESTS_SH=	integration_test

.include <bsd.test.mk>
