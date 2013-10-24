#	$NetBSD$

.PATH: ${.CURDIR}/nls

SRCS+=	catclose.c catgets.c catopen.c 
MAN+=	catclose.3 catgets.3 catopen.3

CPPFLAGS.catopen.c+=	-I${LIBCDIR}/citrus

