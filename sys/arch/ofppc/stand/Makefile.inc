#	$NetBSD$

BINDIR=		/usr/mdec

CPPFLAGS+=	-D_STANDALONE

CFLAGS+=	${${ACTIVE_CC} == "gcc":? -msoft-float :}
