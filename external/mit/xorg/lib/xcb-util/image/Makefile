#	$NetBSD$

XCBUTIL=	image

SRCS=	\
	xcb_image.c

XCBUTIL_EXTRA_DPLIBS+=\
	xcb-shm	${.CURDIR}/../../libxcb/shm \
	xcb-aux	${.CURDIR}/../aux

.include "../xcb-util.mk"

CPPFLAGS+=	-I${X11SRCDIR.xcb-util}/aux

CWARNFLAGS.clang+=	-Wno-return-type
