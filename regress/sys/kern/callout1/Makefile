#	$NetBSD$

KMOD=   callout1_test

NOMAN=

.PATH:	${.CURDIR}/../lkmcommon

SRCS=	lkminit_test.c test_callout1.c
CPPFLAGS+=-DLKMENTRY=callout1_test_lkmentry

.include <bsd.kmod.mk>
.include <bsd.subdir.mk>
