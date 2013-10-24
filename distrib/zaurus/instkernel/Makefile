#	$NetBSD$

.include <bsd.own.mk>
.include "${NETBSDSRCDIR}/distrib/common/Makefile.distrib"

RAMDISKDIR!=	cd ${.CURDIR}/../ramdisk && ${PRINTOBJDIR}
RAMDISK=	${RAMDISKDIR}/ramdisk.fs

MDSETTARGETS=		INSTALL ${RAMDISK} netbsd-INSTALL \
			INSTALL_C700 ${RAMDISK} netbsd-INSTALL_C700

MDSET_RELEASEDIR=	installation/kernel

MDSET_NOGZIP=		# defined
MDSET_NOSTRIP=		# defined
MDSET_NOSYMBOLS=	# defined

.include "${DISTRIBDIR}/common/Makefile.mdset"

.include <bsd.prog.mk>
