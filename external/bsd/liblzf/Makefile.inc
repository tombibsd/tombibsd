# $NetBSD$
.include <bsd.own.mk>

USE_FORT?=	yes	# data-driven bugs?

LIBLZFDIR=	${NETBSDSRCDIR}/external/bsd/liblzf
.PATH:          ${LIBLZFDIR}/dist
CPPFLAGS+=	-I ${LIBLZFDIR}/dist
