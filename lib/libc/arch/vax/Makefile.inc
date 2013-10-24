#	$NetBSD$

SRCS+=	__longjmp14.c
SRCS+=	__sigaction14_sigtramp.c __sigtramp3.S

CPPFLAGS+= -I.
CPPFLAGS.assym.h+=-D__LIBC12_SOURCE__
