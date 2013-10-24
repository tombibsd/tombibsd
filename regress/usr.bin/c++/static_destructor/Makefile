# $NetBSD$

PROG_CXX=	static_destructor
NOMAN=		# defined

regress:
	./${PROG} > out && diff out ${.CURDIR}/expected

CLEANFILES+=	out

.include <bsd.prog.mk>
