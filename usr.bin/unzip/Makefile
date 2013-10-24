# $NetBSD$

PROG=	unzip

DPADD+=		${LIBARCHIVE} ${LIBZ} ${LIBBZ2}
LDADD+=		-larchive -lz -lbz2

COPTS.unzip.c += -Wno-format-y2k

.include <bsd.prog.mk>
