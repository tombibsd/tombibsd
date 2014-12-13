#	$NetBSD$

KMINCLUDES=
KMSRCS=	

CPPFLAGS+=	-I.

SRCS+=		__sigaction14_sigtramp.c __sigtramp2.S
