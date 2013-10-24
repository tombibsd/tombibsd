#	$NetBSD$

PIXELSIZE=	8

.include "../Makefile.serverlib"

SRCS=	cfbcmap.c

.include "Makefile.cfb"

.if defined(X11FLAGS.LOADABLE)
SUBDIR= module
.include <bsd.subdir.mk>
.endif
