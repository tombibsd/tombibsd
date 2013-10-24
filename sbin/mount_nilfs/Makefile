#	$NetBSD$

.include <bsd.own.mk>

PROG=	mount_nilfs
SRCS=	mount_nilfs.c fattr.c pathadj.c
MAN=	mount_nilfs.8

MOUNT=	${NETBSDSRCDIR}/sbin/mount
CPPFLAGS+= -I${MOUNT} -I${NETBSDSRCDIR}/sys
.PATH:	${MOUNT}

DPADD+=${LIBUTIL}
LDADD+=-lutil

.include <bsd.prog.mk>
