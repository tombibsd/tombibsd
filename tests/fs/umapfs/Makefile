#	$NetBSD$
#

TESTSDIR=	${TESTSBASE}/fs/umapfs
WARNS=		4

TESTS_C=	t_basic

LDADD+=	-lrumpfs_tmpfs -lrumpfs_umap -lrumpvfs_layerfs		# fs drivers
LDADD+=	-lrumpvfs -lrump -lrumpuser -lrump -lpthread		# base

.include <bsd.test.mk>
