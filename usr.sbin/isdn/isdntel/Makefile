#	$NetBSD$

PROG	 =	isdntel
SRCS	 =	main.c display.c files.c alias.c
LDADD	+=	-lcurses -lterminfo
MAN      =	isdntel.8

.include <bsd.prog.mk>

COPTS.alias.c+=		-Wno-pointer-sign
COPTS.files.c+=		-Wno-format-nonliteral
