#	$NetBSD$

PIXELSIZE=	24

.include "../Makefile.serverlib"
.include "../cfb/Makefile.cfb"

.if defined(X11FLAGS.LOADABLE)
SUBDIR= module
.include <bsd.subdir.mk>
.endif
