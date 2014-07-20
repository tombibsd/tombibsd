#	$NetBSD$

LIB=irs
#USE_SHLIBDIR=   yes

.include <bsd.own.mk>

.include "${.CURDIR}/../Makefile.inc"

CPPFLAGS+= -I${DIST}/include -I${IDIST}/lib/irs/include

DIST=   ${IDIST}/lib/irs
.include "${DIST}/api"

.PATH.c:	${DIST}

SRCS=		context.c dnsconf.c gai_strerror.c getaddrinfo.c \
		getnameinfo.c resconf.c version.c


.include <bsd.lib.mk>
