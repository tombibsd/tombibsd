#	$NetBSD$

.include <bsd.own.mk>

PROG=	mount_sysvbfs
SRCS=	mount_sysvbfs.c fattr.c pathadj.c
MAN=	mount_sysvbfs.8

MOUNT=	${NETBSDSRCDIR}/sbin/mount
CPPFLAGS+= -I${MOUNT}
.PATH:	${MOUNT}

DPADD+=${LIBUTIL}
LDADD+=-lutil

.include <bsd.prog.mk>
