#	$NetBSD$

.include "Makefile.inc"

.include <bsd.own.mk>

.if ${MKSHARE} != "no"
SUBDIR+= catalog
.endif

SUBDIR+= build recover

.if ${MKDOC} != "no"
SUBDIR+= docs
.endif

.include <bsd.subdir.mk>
