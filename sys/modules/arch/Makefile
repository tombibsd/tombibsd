#	$NetBSD$

# Build multi-abi kernel modules

.include <bsd.own.mk>

.if ${MKCOMPATMODULES} != "no"
.if !make(includes)

.include "archdirs.mk"

SUBDIR=	dirshack .WAIT ${ARCHDIR_SUBDIR}

.endif
.endif

.include <bsd.subdir.mk>
