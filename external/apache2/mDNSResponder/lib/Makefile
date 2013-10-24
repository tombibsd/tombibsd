#	$NetBSD$

.include <bsd.init.mk>

LIB=	dns_sd

SRCS=	dnssd_clientlib.c dnssd_clientstub.c dnssd_ipc.c  
CPPFLAGS+=-I${DIST}/mDNSShared

COPTS.dnssd_clientstub.c += -Wno-stack-protector

INCS=	dns_sd.h
INCSDIR=/usr/include

.PATH:	${DIST}/mDNSShared

zoot:
	ls ${DIST}/mDNSShared/dnssd_clientlib.c
	
.include <bsd.lib.mk>
