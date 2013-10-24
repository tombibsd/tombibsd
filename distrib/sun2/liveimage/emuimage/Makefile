#	$NetBSD$

LIVEIMGBASE=	NetBSD-${DISTRIBVER}-sun2-live-sd0root	# gives ${IMGBASE}.img

.include <bsd.own.mk>

KERN_SET=		kern-GENERIC
BOOTDISK=		sd0
.if defined(EMUIMAGEMB)
LIVEIMAGEMB=		${EMUIMAGEMB}
.endif
PRIMARY_BOOT=		bootxx
SECONDARY_BOOT=		ufsboot
SECONDARY_BOOT_ARG=	/${SECONDARY_BOOT}

#USE_SUNLABEL=		yes		# sun2 PROM doesn't read sunlabel

.include "${.CURDIR}/../../../common/bootimage/Makefile.liveimage"
