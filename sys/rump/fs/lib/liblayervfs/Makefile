#	$NetBSD$
#

.PATH:  ${.CURDIR}/../../../../miscfs/genfs

LIB=	rumpvfs_layerfs

SRCS=	layer_subr.c layer_vfsops.c layer_vnops.c

CWARNFLAGS.clang+=	-Wno-conversion

.include <bsd.lib.mk>
.include <bsd.klinks.mk>
