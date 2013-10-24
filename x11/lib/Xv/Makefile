#	$NetBSD$

.include <bsd.own.mk>

LIB=	Xv
.PATH:	${X11SRCDIR.xc}/lib/${LIB}

SRCS=	Xv.c

CPPFLAGS+=	${X11FLAGS.THREADS}

LIBDPLIBS=\
	Xext	${.CURDIR}/../Xext \
	X11	${.CURDIR}/../X11/dynamic

.include <bsd.x11.mk>
.include <bsd.lib.mk>
