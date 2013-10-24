#	$NetBSD$
#

RUMPTOP=	${.CURDIR}/../../sys/rump

LIBDPLIBS+=	rump	${.CURDIR}/../librump

WARNS=		3	# XXX: kernel isn't ready for -Wsign-compare

.include "${RUMPTOP}/librump/rumpdev/Makefile.rumpdev"
