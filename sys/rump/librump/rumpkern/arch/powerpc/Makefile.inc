# $NetBSD$

.if ${MACHINE_ARCH} == "powerpc"
CPPFLAGS+=	-DARCH_ELFSIZE=32
.else
CPPFLAGS+=	-DARCH_ELFSIZE=64
.endif
SRCS+=  	kobj_stubs.c rumpcpu_generic.c
