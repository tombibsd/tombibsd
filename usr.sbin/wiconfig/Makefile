#	$NetBSD$

PROG=	wiconfig
MAN=	wiconfig.8

.include <bsd.prog.mk>

.if defined(HAVE_GCC) || defined(HAVE_LLVM)
COPTS+=	-fno-strict-aliasing
.endif
