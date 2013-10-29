#	$NetBSD$
.include <bsd.own.mk>

SUBDIR=	 libevent .WAIT
.if ${MKCRYPTO} != "no"
SUBDIR+=	libevent_openssl
.endif
SUBDIR+= libevent_pthreads

.include <bsd.subdir.mk>
