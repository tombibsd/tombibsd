#	$NetBSD$

.include <bsd.own.mk>

LIB=event_openssl

SRCS= \
bufferevent_openssl.c

LIBDPLIBS+= \
	event	${.CURDIR}/../libevent \
	crypto	${NETBSDSRCDIR}/crypto/external/bsd/openssl/lib/libcrypto \
	ssl	${NETBSDSRCDIR}/crypto/external/bsd/openssl/lib/libssl

.include <bsd.lib.mk>
