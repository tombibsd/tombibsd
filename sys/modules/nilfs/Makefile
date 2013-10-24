#	$NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/fs/nilfs

KMOD=  	nilfs
SRCS=	nilfs_vfsops.c nilfs_vnops.c nilfs_subr.c

CWARNFLAGS.clang=	-Wno-self-assign

.include <bsd.kmodule.mk>
