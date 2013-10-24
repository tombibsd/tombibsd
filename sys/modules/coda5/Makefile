#	$NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/coda 

KMOD=	coda5
SRCS=	coda_namecache.c coda_psdev.c coda_subr.c coda_venus.c \
	coda_vfsops.c coda_vnops.c

CPPFLAGS+=	-DCODA_COMPAT_5

.include <bsd.kmodule.mk>
