#	$NetBSD$
#

RUMPTOP=	${.CURDIR}/../../..

CPPFLAGS+=	-I${RUMPTOP}/librump/rumpdev -I${RUMPTOP}/librump/rumpkern

.include "${RUMPTOP}/Makefile.rump"
