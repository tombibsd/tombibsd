#	$NetBSD$

SRCS+=		__sigaction14_sigtramp.c __sigtramp2.S
SRCS+=		powerpc_initfini.c

CPPFLAGS+=	-I.

.if defined(MKSOFTFLOAT) && (${MKSOFTFLOAT} != "no")
.include <softfloat/Makefile.inc>
.endif
