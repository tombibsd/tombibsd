#	$NetBSD$

.include <bsd.own.mk>
.include "${NETBSDSRCDIR}/distrib/common/Makefile.distrib"

RAMDISKDIR!=	cd ${.CURDIR}/../ramdisk && ${PRINTOBJDIR}
RAMDISK=	${RAMDISKDIR}/ramdisk.fs

MDSETTARGETS=		INSTALL ${RAMDISK} install.ram
MDSET_RELEASEDIR=	installation/netboot

.include "${DISTRIBDIR}/common/Makefile.mdset"

.include <bsd.prog.mk>
