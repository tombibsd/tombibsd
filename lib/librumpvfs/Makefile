#	$NetBSD$
#

RUMPTOP=	${.CURDIR}/../../sys/rump

LIBDPLIBS+=     rump	${.CURDIR}/../librump
MAN=		rump_etfs.3 rumpfs.4

WARNS=		3	# XXX: kernel isn't ready for -Wsign-compare

.include "${RUMPTOP}/librump/rumpvfs/Makefile.rumpvfs"
