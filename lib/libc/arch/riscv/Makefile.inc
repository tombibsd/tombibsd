#	$NetBSD$

SRCS+=		__sigaction14_sigtramp.c __sigtramp2.S

CPPFLAGS+=	-I.

.if ${MKSOFTFLOAT} != "no"
.include <softfloat/Makefile.inc>
.endif
