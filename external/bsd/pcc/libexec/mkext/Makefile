#	$NetBSD$

#
# this is really part of ccom, but HOSTPROG and PROG don't mix
#

.include <bsd.init.mk>

.PATH:	${PCC_DIST}/mip \
	${PCC_DIST}/arch/${TARGMACH}

HOSTPROG=	mkext
MAN=
SRCS=		mkext.c table.c common.c

HOST_CPPFLAGS+=	-DMKEXT
HOST_CPPFLAGS+=	-DGCC_COMPAT
HOST_CPPFLAGS+=	-Dos_${TARGOS}
HOST_CPPFLAGS+=	-Dmach_${TARGMACH}
HOST_CPPFLAGS+=	-I${PCC_DIST}/mip
HOST_CPPFLAGS+=	-I${PCC_DIST}/arch/${TARGMACH}
HOST_CPPFLAGS+=	-I${PCC_DIR}/include

.include <bsd.hostprog.mk>
