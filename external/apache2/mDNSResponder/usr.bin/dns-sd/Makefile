#	$NetBSD$

PROG=	dns-sd

.include <bsd.init.mk>

.PATH:	${DIST}/Clients ${DIST}/mDNSShared

SRCS=	dns-sd.c ClientCommon.c
LDADD+= -ldns_sd
DPADD+= ${LIBDNS_SD}

.include <bsd.prog.mk>
