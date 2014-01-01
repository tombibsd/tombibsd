#	$NetBSD$
#

.include <bsd.own.mk>

SMBDIST=${NETBSDSRCDIR}/external/bsd/smbfs/dist

CPPFLAGS+= -I${SMBDIST}/include
