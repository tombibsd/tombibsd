#	$NetBSD$
#

PROG=	ms

LDADD+=	-lrumpdev_ums -lrumpdev_wscons -lrumpdev_usb -lrumpdev_ugenhc -lrumpdev
LDADD+=	-lrumpvfs
LDADD+=	-lrump
LDADD+=	-lrumpuser -lpthread

LDADD+=	-lcurses

DBG=	-g
NOMAN=	
WARNS=	4

.include <bsd.prog.mk>
