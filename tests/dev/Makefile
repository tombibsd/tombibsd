#	$NetBSD$
#

.include <bsd.own.mk>

TESTSDIR=	${TESTSBASE}/dev

TESTS_SUBDIRS+=	cgd raidframe
.if (${MKRUMP} != "no")
TESTS_SUBDIRS+=	audio md scsipi sysmon
.endif


.include <bsd.test.mk>
