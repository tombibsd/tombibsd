#	$NetBSD$

IMAGE=		generic.fs
BOOTLOADER=	${MDEC}/boot

.include <bsd.own.mk>
KERNDIR!=	cd ${.CURDIR}/../kernel-generic && ${PRINTOBJDIR}
KERNEL=		${KERNDIR}/netbsd-GENERIC.gz

.include "../bootfloppy-common/Makefile.inc"
