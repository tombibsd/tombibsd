#	$NetBSD$

.include <bsd.own.mk>

PROG=	resize
SRCS=	resize.c xstrings.c

CPPFLAGS+=-I${X11SRCDIR.xc}/programs/xterm

.PATH:	${X11SRCDIR.xc}/programs/xterm

.include <bsd.x11.mk>
.include <bsd.prog.mk>
