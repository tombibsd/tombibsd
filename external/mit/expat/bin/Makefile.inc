#	$NetBSD$

BINDIR?=	/usr/bin

CPPFLAGS+=	-I${EXPATSRCDIR}/lib

LDADD+=	-L${EXPATOBJDIR.expat} -lexpat
DPADD+=	${EXPATLIB.expat}

.include "../Makefile.inc"
