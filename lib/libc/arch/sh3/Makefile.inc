#	$NetBSD$

SRCS+=	__sigaction14_sigtramp.c __sigtramp2.S

CPPFLAGS+=      -DSOFTFLOAT # -DSOFTFLOAT_NEED_FIXUNS
.include <softfloat/Makefile.inc>
