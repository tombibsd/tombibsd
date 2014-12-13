#	$NetBSD$
#

TESTSDIR=	${TESTSBASE}/fs/kernfs
WARNS=		4

TESTS_C=	t_basic

.include <bsd.own.mk>

LDADD+=	-lrumpfs_kernfs						# fs driver
LDADD+=	-lrumpvfs -lrump -lrumpuser -lrump -lpthread		# base

.include <bsd.test.mk>
