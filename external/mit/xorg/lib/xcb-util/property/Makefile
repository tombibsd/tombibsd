#	$NetBSD$

XCBUTIL=	property

SRCS=	property.c

SHLIB_MAJOR=	1

XCBUTIL_EXTRA_DPLIBS+=\
	xcb-event	${.CURDIR}/../event

.include "../xcb-util.mk"

CPPFLAGS+=	-I${X11SRCDIR.xcb-util}/event
