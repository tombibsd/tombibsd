#	$NetBSD$
.PATH.c: ${.PARSEDIR}
SRCS+=	snprintb.c proc_compare.c getfstypename.c
COPTS.snprintb.c = -Wno-format-nonliteral
