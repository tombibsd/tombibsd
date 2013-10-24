#	$NetBSD$

.include <bsd.own.mk>

# Our sources
.PATH: ${.CURDIR}/thread-stub

SRCS+=	__isthreaded.c thread-stub.c thread-stub-init.c
