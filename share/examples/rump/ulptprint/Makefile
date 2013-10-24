#	$NetBSD$
#

PROG=	ulptprint

LDADD+=	-lrumpvfs -lrumpdev_usb -lrumpdev_ugenhc -lrumpdev_ulpt -lrumpdev
LDADD+=	-lrump
LDADD+=	-lrumpuser -lpthread

DBG=	-g
NOMAN=	
WARNS=	4

.include <bsd.prog.mk>
