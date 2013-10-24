#	$NetBSD$

.include <bsd.own.mk>
.include <bsd.init.mk>

.include "${.CURDIR}/../../arch/${GCC_MACHINE_ARCH}/defs.mk"

.cc: # disable .cc->NULL transform

DIST=		${NETBSDSRCDIR}/external/gpl3/gcc/dist

INCS=		${G_parallel_headers}
INCSDIR=	/usr/include/g++/parallel

.PATH: ${DIST}/libstdc++-v3/include/parallel

# Get default targets including <bsd.inc.mk>.
.include <bsd.prog.mk>
