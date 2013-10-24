#	$NetBSD$

IMAGESIZE=	7m
IMAGEENDIAN=	be
MAKEDEVTARGETS=	all ipty
MAKEFS_FLAGS=	-o density=4k
IMAGEDEPENDS+=	${ARCHDIR}/dot.profile ${ARCHDIR}/install.md \
		${KERNOBJDIR}/INSTALL/netbsd
