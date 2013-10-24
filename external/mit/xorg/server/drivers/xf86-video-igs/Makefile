#	$NetBSD$

DRIVER=		xf86-video-igs
DRIVER_NAME=	igs_drv

SRCS=		igs_driver.c igs_cursor.c igs_accel.c
MAN=		igs.4

CPPFLAGS+=	-DHAVE_CONFIG_H -I${X11SRCDIR.${DRIVER}}/../include

.include "../Makefile.xf86-driver"
