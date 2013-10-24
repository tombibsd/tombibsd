#	$NetBSD$

.include <bsd.own.mk>
.include "${NETBSDSRCDIR}/distrib/common/Makefile.distrib"

NCDCS = ${TOOLDIR}/bin/${_TOOL_PREFIX}ibmnws-ncdcs

RAMDISKDIR!=	cd ${.CURDIR}/../ramdisk && ${PRINTOBJDIR}
RAMDISK=	${RAMDISKDIR}/ramdisk.fs

MDSETTARGETS=		GENERIC		${RAMDISK}	-
MDSET_RELEASEDIR=	binary/kernel

MDSET_POST.- = \
	${NCDCS} ${.TARGET} ${.TARGET}.1000

.include "${DISTRIBDIR}/common/Makefile.mdset"

.include <bsd.prog.mk>
