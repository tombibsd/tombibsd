#	$NetBSD$

NOMAN=	# defined

PROG=	sgivol
.if (${HOSTPROG:U} == "")
DPADD+=	${LIBUTIL}
LDADD+=	-lutil
.endif

WARNS=	2

.include <bsd.prog.mk>
