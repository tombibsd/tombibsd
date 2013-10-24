#	$NetBSD$

PROG=	mount_sysctlfs
SRCS=	sysctlfs.c

DPAPP+=	${LIBPUFFS} ${LIBUTIL}
LDADD+=	-lpuffs -lutil

MAN=	mount_sysctlfs.8

.ifdef RUMP_ACTION
CPPFLAGS+=	-DRUMP_ACTION
LDADD+=		-lrump -lrumpuser -lpthread
.endif

.include <bsd.prog.mk>
