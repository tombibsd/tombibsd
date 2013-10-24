# $NetBSD$

# objects built from assembler sources
SRCS+=  compat_setjmp.S compat__setjmp.S compat_sigsetjmp.S

# objects built from C sources in compat/gen
SRCS+=  compat_frexp_ieee754.c compat_ldexp_ieee754.c compat_modf_ieee754.c
