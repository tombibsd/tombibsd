#	$NetBSD$

.include <bsd.own.mk>

LIB=	dmx
.PATH:	${X11SRCDIR.xc}/lib/dmx

SRCS=	dmx.c

CPPFLAGS+=	-I${X11SRCDIR.xc}/include/extensions
CPPFLAGS+=	${X11FLAGS.THREADS}

LIBDPLIBS=\
	Xext	${.CURDIR}/../Xext \
	X11	${.CURDIR}/../X11/dynamic

.include <bsd.x11.mk>
.include <bsd.lib.mk>
