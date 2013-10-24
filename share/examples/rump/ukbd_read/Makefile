#	$NetBSD$
#

PROG=	kbd

LDADD+=	-lrumpdev_ukbd -lrumpdev_wscons -lrumpdev_usb -lrumpdev_ugenhc -lrumpdev
LDADD+=	-lrumpvfs
LDADD+=	-lrump
LDADD+=	-lrumpuser -lpthread

DBG=	-g
NOMAN=	
WARNS=	4

.include <bsd.prog.mk>
