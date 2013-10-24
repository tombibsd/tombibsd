#	$NetBSD$

.include <bsd.own.mk>
.include "${NETBSDSRCDIR}/distrib/common/Makefile.distrib"

RAMDISKDIR!=	cd ${.CURDIR}/../ramdisk && ${PRINTOBJDIR}
RAMDISK=	${RAMDISKDIR}/ramdisk.fs

.if ${MACHINE_ARCH} == "mips64el"
SFX=		64
.endif

MDSETTARGETS=		RAMDISK${SFX} ${RAMDISK} -
MDSET_RELEASEDIR=	binary/kernel

# do not strip kernels, there's no space constraints here.
MDSET_NOSTRIP.netbsd-RAMDISK${SFX}=
MDSET_NOSYMBOLS.netbsd-RAMDISK${SFX}=

.include "${DISTRIBDIR}/common/Makefile.mdset"

.include <bsd.prog.mk>
