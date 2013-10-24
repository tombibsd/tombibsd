# $NetBSD$

.include <bsd.own.mk>

SUBDIR= 	hello

.if ${MKSHARE} != "no"
FILES=		Makefile.inc.inst README
FILESDIR=	/usr/share/examples/asm
FILESNAME_Makefile.inc.inst=	Makefile.inc
.endif

.include <bsd.files.mk>
.include <bsd.subdir.mk>
