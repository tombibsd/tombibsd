#	$NetBSD$

.include <bsd.own.mk>

LIB=event_openssl

SRCS= \
bufferevent_openssl.c

LIBDPLIBS+=     crypto  ${NETBSDSRCDIR}/crypto/external/bsd/openssl/lib/libcrypto \
	crypt  ${NETBSDSRCDIR}/lib/libcrypt

.include <bsd.lib.mk>
