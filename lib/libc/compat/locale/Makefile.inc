# $NetBSD$

.PATH: ${COMPATDIR}/arch/${MACHINE_ARCH}/locale ${COMPATDIR}/locale

CPPFLAGS+=	-I${COMPATDIR}/../locale
SRCS+=		compat_setlocale1.c compat_setlocale32.c
