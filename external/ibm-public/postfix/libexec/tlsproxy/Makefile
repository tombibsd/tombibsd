#	$NetBSD$

NOMAN=	# defined

.include <bsd.own.mk>

PROG=	tlsproxy

DIST=	${NETBSDSRCDIR}/external/ibm-public/postfix/dist/src/${PROG}
.PATH:	${DIST}

SRCS=   tlsproxy_state.c tlsproxy.c

DPADD+= ${LIBPTLS} ${LIBPMASTER} ${LIBPGLOBAL} ${LIBPUTIL}
LDADD+= ${LIBPTLS} ${LIBPMASTER} ${LIBPGLOBAL} ${LIBPUTIL}

DPADD+= ${LIBSSL} ${LIBCRYPTO}
LDADD+= -lssl -lcrypto

.include <bsd.prog.mk>
