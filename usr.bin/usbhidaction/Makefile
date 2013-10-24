#	$NetBSD$

.include <bsd.own.mk>

PROG=	usbhidaction
SRCS=	usbhidaction.c

LDADD+=	-lusbhid -lutil
DPADD+=	${LIBUSBHID} ${LIBUTIL}

.include <bsd.prog.mk>
.include <bsd.subdir.mk>
