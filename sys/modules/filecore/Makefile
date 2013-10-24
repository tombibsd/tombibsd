#	$NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/fs/filecorefs

KMOD=	filecore
SRCS=	filecore_bmap.c filecore_lookup.c filecore_node.c filecore_utils.c \
	filecore_vfsops.c filecore_vnops.c

.include <bsd.kmodule.mk>
