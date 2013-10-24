# $NetBSD$

NOLINT=		# defined

.include <bsd.own.mk>
.include <${.CURDIR}/../../Makefile.inc>

.PATH:		${HEIMDIST}/lib/ipc

LIB=		ipc

LIBDPLIBS+=	util ${NETBSDSRCDIR}/lib/libutil \
		crypt ${NETBSDSRCDIR}/lib/libcrypt

SRCS= common.c client.c server.c

HOST_CPPFLAGS+=	-I${HEIMBASE}/include -DHAVE_CONFIG_H

libinstall::

.include <${HEIMBASE}/Makefile.rules.inc>
.include <bsd.lib.mk>
