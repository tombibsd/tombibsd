# $NetBSD$

.include "../Makefile.inc"

BINDIR=		/usr/bin

CPPFLAGS+=	-I${LESS_DISTDIR} -DBINDIR=\"${BINDIR}\" -DSYSDIR=\"/etc\"
