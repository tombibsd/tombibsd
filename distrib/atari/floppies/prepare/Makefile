#	$NetBSD$

IMAGE=		prepare.fs
IMAGESIZE?=	1080k
MAKEDEVTARGETS=	floppy
IMAGEDEPENDS+=	install.sh install.md ${.CURDIR}/../../../miniroot/install.sub
PARSELISTENV=	DISTRIBREV=${DISTRIBREV:Q}

.include "../common/Makefile.images"
