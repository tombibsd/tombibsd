# $NetBSD$

SRCS+=		rtld_start.S mdreloc.c

# XXX Should not be in CPPFLAGS!
CPPFLAGS+=	-fpic

.if ${LDELFSO_MACHINE_ARCH} == "riscv64"
CPPFLAGS+=	-DELFSIZE=64
.else
CPPFLAGS+=	-DELFSIZE=32
.endif
CPPFLAGS+=	-DHAVE_INITFINI_ARRAY

LDFLAGS+=	-Wl,-e,_rtld_start
