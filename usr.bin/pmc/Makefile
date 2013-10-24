#	$NetBSD$

.if (${MACHINE_ARCH} == "i386")
PROG=	pmc

LDADD+=	-li386
DPADD+=	${LIBI386}
.else
MAN=	pmc.1
.endif

.include <bsd.prog.mk>
