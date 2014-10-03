#	$NetBSD$

SRCS+=		mdreloc.c
LDFLAGS+=	-Wl,-e,_rtld_start

CPPFLAGS+=	-fPIC

SRCS+=		rtld_start.S
CPPFLAGS+=	-DELFSIZE=32
#LDFLAGS+=	-Wl,--script,${.CURDIR}/arch/powerpc/ld.so.script
