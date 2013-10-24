#	$NetBSD$

PROG=	mopcopy

.include <bsd.own.mk>
.if ${MACHINE_CPU} == "mips"
CFLAGS+= -DNOAOUT
.endif

.include <bsd.prog.mk>
