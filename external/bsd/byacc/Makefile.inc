#	$NetBSD$

WARNS=4

.include <bsd.own.mk>

BINDIR?= /usr/bin

IDIST=	${NETBSDSRCDIR}/external/bsd/byacc/dist

CPPFLAGS+= -DHAVE_CONFIG_H -I${.CURDIR}/../include -I${IDIST}
CWARNFLAGS+=	-Wno-missing-noreturn

.PATH: ${IDIST}
