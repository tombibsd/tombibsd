#	$NetBSD$
#

.PATH:	${.CURDIR}/ffs ${NETBSDSRCDIR}/sys/ufs/ffs

SRCS+=	ffs_alloc.c ffs_balloc.c ffs_bswap.c ffs_subr.c ffs_tables.c ufs_bmap.c
SRCS+=	buf.c mkfs.c
