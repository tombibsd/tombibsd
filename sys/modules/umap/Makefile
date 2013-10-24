#	$NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/miscfs/umapfs

KMOD=	umap
SRCS=	umap_vfsops.c umap_vnops.c umap_subr.c

CWARNFLAGS.clang=	-Wno-conversion

.include <bsd.kmodule.mk>
