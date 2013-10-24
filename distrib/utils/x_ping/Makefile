# $NetBSD$
# Build ping without IPSEC

SRCDIR=		${.CURDIR}/../../../sbin/ping

PROG=		ping
NOMAN=		# defined

CPPFLAGS+=	-I${SRCDIR} -DCRUNCHOPS
DPADD=		${LIBM}
LDADD=		-lm

.include <bsd.prog.mk>

.PATH:		${SRCDIR}
