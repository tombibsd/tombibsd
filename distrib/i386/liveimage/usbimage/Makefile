#	$NetBSD$

LIVEIMGBASE=	NetBSD-${DISTRIBVER}-i386-live-sd0root	# gives ${IMGBASE}.img

USBIMAGEMB?=	1536            	# 2GB USB flash memories aren't 2GiB

BOOTDISK=	sd0			# for USB flash etc.
LIVEIMAGEMB=	${USBIMAGEMB}
OMIT_SWAPIMG=	yes			# no need to write swap

.include "${.CURDIR}/../Makefile.liveimage"
