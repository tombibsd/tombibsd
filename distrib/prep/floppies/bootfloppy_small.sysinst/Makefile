#	$NetBSD$

IMAGE=		sysinst_small.fs
BOOTLOADER=	${MDEC}/boot

.include <bsd.own.mk>
KERNDIR!=	cd ${.CURDIR}/../kernel-ramdisk && ${PRINTOBJDIR}
KERNEL=		${KERNDIR}/netbsd-INSTALL_SMALL.gz

.include "../bootfloppy-common/Makefile.inc"
