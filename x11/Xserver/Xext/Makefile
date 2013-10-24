#	$NetBSD$

SUBDIR=	ext exts

.include "../Makefile.serverlib"
.include "Makefile.ext"

.if defined(X11FLAGS.LOADABLE)
SUBDIR+=	extmod
.endif

.include <bsd.subdir.mk>
