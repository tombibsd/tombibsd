#	$NetBSD$

KMOD=   mutex1_test

NOMAN=

.PATH:	${.CURDIR}/../lkmcommon

SRCS=	lkminit_test.c test_mutex1.c
CPPFLAGS+=-DLKMENTRY=mutex1_test_lkmentry

.include <bsd.kmod.mk>
.include <bsd.subdir.mk>
