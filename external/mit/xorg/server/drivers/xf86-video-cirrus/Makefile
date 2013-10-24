#	$NetBSD$

DRIVER=		xf86-video-cirrus
DRIVER_NAME=	cirrus_drv

SRCS=		cir_dga.c cir_driver.c CirrusClk.c cir_shadow.c
MAN=		cirrus.4

CPPFLAGS.cir_driver.c=	-DVERSION=${PACKAGE_MAJOR}

.include "../Makefile.xf86-driver"
