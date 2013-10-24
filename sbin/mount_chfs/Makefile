# $NetBSD$
#
.include <bsd.own.mk>

PROG=		mount_chfs
SRCS=		mount_chfs.c fattr.c pathadj.c
MAN=		mount_chfs.8

MOUNT=		${NETBSDSRCDIR}/sbin/mount
.PATH:		${MOUNT}

CPPFLAGS+=	-I${MOUNT}
DPADD+=		${LIBUTIL}
LDADD+=		-lutil

.include <bsd.prog.mk>
