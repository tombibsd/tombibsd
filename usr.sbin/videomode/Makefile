#	$NetBSD$

NOMAN=	# defined
.include <bsd.own.mk>

.if ${MACHINE} == "amiga"
PROG=videomode
CPPFLAGS+=-I${NETBSDSRCDIR}/sys/arch -D${MACHINE}
.endif

.include <bsd.prog.mk>
