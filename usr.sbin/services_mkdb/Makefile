#	$NetBSD$

PROG=	services_mkdb
MAN=	services_mkdb.8
SRCS=	services_mkdb.c output_cdb.c output_db.c uniq.c

LDADD+=	-lutil
DPADD+=	${LIBUTIL}
#COPTS+=-g

.include <bsd.prog.mk>
