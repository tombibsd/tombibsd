#	$NetBSD$

SRCS+=		rtld_start.S mdreloc.c

# XXX Should not be in CPPFLAGS!
CPPFLAGS+=	-fPIC

CPPFLAGS+=	-DELFSIZE=64

LDFLAGS+=	-Wl,-e,.rtld_start
