#	$NetBSD$

.include "../Makefile.serverlib"
.include "Makefile.fb"

CPPFLAGS.fbbltone.c=	-Wno-error

.if defined(X11FLAGS.LOADABLE)
SUBDIR=	module
.include <bsd.subdir.mk>
.endif
