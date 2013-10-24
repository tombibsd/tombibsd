# $NetBSD$

TESTSDIR=	${TESTSBASE}/lib/libobjc

.include <bsd.own.mk>

UNSUPPORTED_COMPILER.clang=	# defined
UNSUPPORTED_COMPILER.pcc=	# defined

.if !empty(AVAILABLE_COMPILER:Mgcc)
TESTS_C=	t_threads
.endif

SRCS.t_threads=	t_threads.m
WARNS?=		4
CFLAGS+=	-pthread
LDFLAGS+=	-pthread
DPADD+=		${LIBOBJC}
LDADD+=		-lobjc

.include <bsd.test.mk>
