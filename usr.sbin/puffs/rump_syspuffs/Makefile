#	$NetBSD$
#

PROG=		rump_syspuffs

LDADD+=		-lrumpfs_syspuffs -lrumpdev_putter
DPADD+=		${LIBRUMPFS_SYSPUFFS}

ISRUMP=		# indubitably
CPPFLAGS+=	-I${.CURDIR}/../../../sys/rump/fs/lib/libsyspuffs
MAN=		rump_syspuffs.8

.include <bsd.prog.mk>
