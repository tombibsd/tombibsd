#	$NetBSD$
#

PROG=	tipsy

LDADD+=	-lrumpvfs
LDADD+=	-lrumpdev_usb -lrumpdev_ugenhc -lrumpdev_ucom -lrumpdev
LDADD+=	-lrumpkern_tty
LDADD+=	-lrump
LDADD+=	-lrumpuser -lpthread

DBG=	-g
NOMAN=	
WARNS=	4

.include <bsd.prog.mk>
