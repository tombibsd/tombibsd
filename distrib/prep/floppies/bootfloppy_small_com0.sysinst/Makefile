#	$NetBSD$

IMAGE=		sysinst_small_com0.fs
BOOTLOADER=	${MDEC}/boot_com0

.include <bsd.own.mk>
KERNDIR!=	cd ${.CURDIR}/../kernel-ramdisk && ${PRINTOBJDIR}
KERNEL=		${KERNDIR}/netbsd-INSTALL_SMALL.gz

.include "../bootfloppy-common/Makefile.inc"
