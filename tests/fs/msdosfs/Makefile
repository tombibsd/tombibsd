#	$NetBSD$
#

TESTSDIR=	${TESTSBASE}/fs/msdosfs
WARNS=		4

TESTS_C=	t_snapshot

LDADD+=-lrumpfs_msdos -lrumpfs_tmpfs				# fs drivers
LDADD+=-lrumpdev_fss						# snapshot dev
LDADD+=-lrumpdev_disk -lrumpdev					# disk device
LDADD+=-lrumpvfs -lrumpkern_sysproxy -lrump -lrumpuser 		# base
LDADD+=-lpthread

.include <bsd.test.mk>
