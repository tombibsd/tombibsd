#	$NetBSD$

.include <bsd.own.mk>

PROG=	mount_hfs
SRCS=	mount_hfs.c pathadj.c
MAN=	mount_hfs.8

MOUNT=	${NETBSDSRCDIR}/sbin/mount
CPPFLAGS+=-I${MOUNT}
.PATH:	${MOUNT}

DPADD+=${LIBUTIL}
LDADD+=-lutil

.include <bsd.prog.mk>
