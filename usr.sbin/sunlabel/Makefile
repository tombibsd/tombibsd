#	$NetBSD$

PROG=	sunlabel
MAN=	sunlabel.8

.ifndef HOSTPROG
LDADD+=	-lterminfo
DPADD+=	${LIBTERMINFO}

DPADD+=	${LIBUTIL}
LDADD+=	-lutil
.endif

.include <bsd.prog.mk>
