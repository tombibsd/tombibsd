#	$NetBSD$

PROG=		infocmp

CPPFLAGS+=	-I${.CURDIR}/../../lib/libterminfo
LDADD+=		-lterminfo
DPADD+=		${LIBTERMINFO}

.include <bsd.prog.mk>
