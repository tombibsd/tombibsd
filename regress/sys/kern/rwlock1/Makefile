#	$NetBSD$

KMOD=   rwlock1_test

NOMAN=

.PATH:	${.CURDIR}/../lkmcommon

SRCS=	lkminit_test.c test_rwlock1.c
CPPFLAGS+=-DLKMENTRY=rwlock1_test_lkmentry

.include <bsd.kmod.mk>
.include <bsd.subdir.mk>
