#	$NetBSD$

.include <bsd.own.mk>

LIB=	Xxf86misc
.PATH:	${X11SRCDIR.xc}/lib/${LIB}

SRCS=	XF86Misc.c

LIBDPLIBS=\
	Xext	${.CURDIR}/../Xext \
	X11	${.CURDIR}/../X11/dynamic

.include <bsd.x11.mk>
.include <bsd.lib.mk>
