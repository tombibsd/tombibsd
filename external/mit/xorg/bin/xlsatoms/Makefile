#	$NetBSD$

.include <bsd.own.mk>

PROG=	xlsatoms

LDADD+=	-lxcb
DPADD+=	${LIBXCB}

.PATH:	${X11SRCDIR.${PROG}}
.PATH:	${X11SRCDIR.${PROG}}/man

.include <bsd.x11.mk>
.include <bsd.prog.mk>
