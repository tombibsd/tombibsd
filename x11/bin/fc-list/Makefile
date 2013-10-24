#	$NetBSD$

.include <bsd.own.mk>

PROG=	fc-list

LDADD+=	-lfontconfig -lfreetype -lexpat
DPADD+=	${LIBFONTCONFIG} ${LIBFREETYPE} ${LIBEXPAT}

.PATH:	${X11SRCDIR.xc}/extras/fontconfig/${PROG}

.include <bsd.x11.mk>
.include <bsd.prog.mk>
