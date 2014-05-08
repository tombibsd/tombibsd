#	$NetBSD$

.include <bsd.own.mk>

PROG=   crunchide
SRCS=	crunchide.c

.for ofmt in ${OBJECT_FMTS}
CPPFLAGS+=	-DNLIST_${ofmt:tu}
SRCS+=		exec_${ofmt}.c
.endfor

.include <bsd.prog.mk>
