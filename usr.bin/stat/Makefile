#	$NetBSD$

PROG=	stat

.if !defined(HOSTPROG)
LINKS=	${BINDIR}/stat ${BINDIR}/readlink
MLINKS=	stat.1 readlink.1
.endif

COPTS.stat.c += -Wno-format-nonliteral

.include <bsd.prog.mk>
