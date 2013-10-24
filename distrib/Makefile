#	$NetBSD$

.include <bsd.own.mk>

.if ${MKGROFF} != "no"
SUBDIR=	notes .WAIT
.endif

SUBDIR+= utils

.if exists(${MACHINE}/miniroot/Makefile.inc)
SUBDIR+= miniroot .WAIT
.endif

.if exists(${RELEASEMACHINE}/Makefile)
SUBDIR+= ${RELEASEMACHINE}
.endif

TARGETS+=release
TARGETS+=iso_image
TARGETS+=live_image
TARGETS+=install_image

.include <bsd.subdir.mk>
