#	$NetBSD$
#

TESTSDIR=	${TESTSBASE}/fs/lfs
WARNS=		4

TESTS_C=	t_pr

LDADD+=-lrumpfs_lfs -lrumpfs_ffs				# fs drivers
LDADD+=-lrumpdev_disk -lrumpdev					# disk device
LDADD+=-lrumpvfs -lrump -lrumpuser -lpthread			# base

.include <bsd.test.mk>
