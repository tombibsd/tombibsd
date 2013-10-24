#	$NetBSD$

.include <bsd.init.mk>

PROG=	xmlwf

.PATH:	${EXPATSRCDIR}/xmlwf ${EXPATSRCDIR}/doc

SRCS=	codepage.c unixfilemap.c xmlfile.c xmlwf.c
CPPFLAGS+=-DHAVE_UNISTD_H

.include <bsd.prog.mk>
