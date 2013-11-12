#	$NetBSD$

.include <bsd.own.mk>

PROG=	lmcconfig
MAN=	lmcconfig.8
CPPFLAGS+=-I${NETBSDSRCDIR}/sys/dev/pci

.if ${MACHINE_ARCH} == "vax"
COPTS.lmcconfig.c=-O0
.endif

.include <bsd.prog.mk>
