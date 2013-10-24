#	$NetBSD$
#

PROG=	sdread

LDADD+=	-lrumpfs_cd9660 -lrumpfs_ffs -lrumpfs_msdos -lrumpvfs
LDADD+=	-lrumpdev_disk -lrumpdev_usb -lrumpdev_ugenhc -lrumpdev_umass
LDADD+=	-lrumpdev_scsipi -lrumpdev
LDADD+=	-lrump
LDADD+=	-lrumpuser -lpthread

DBG=	-g
NOMAN=	
WARNS=	4

.include <bsd.prog.mk>
