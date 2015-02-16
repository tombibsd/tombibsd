#	$NetBSD$
#
PROG=txlt
NOMAN=	# defined
CLEANFILES+=	txlt.c

.ifndef HOSTPROG
LDADD+=		-ll
DPADD+=		${LIBL}
.endif

.include <bsd.prog.mk>
