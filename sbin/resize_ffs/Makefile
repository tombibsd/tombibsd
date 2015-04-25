#	$NetBSD$

.include <bsd.own.mk>

PROG=resize_ffs
MAN=resize_ffs.8
SRCS=resize_ffs.c ffs_bswap.c progress.c

CPPFLAGS+=-I${NETBSDSRCDIR}/sbin/fsck

.PATH: ${NETBSDSRCDIR}/sys/ufs/ffs
.PATH: ${NETBSDSRCDIR}/sbin/fsck

.include <bsd.prog.mk>
