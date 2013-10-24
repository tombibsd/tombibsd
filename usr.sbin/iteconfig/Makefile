#   $NetBSD$

.include <bsd.own.mk>

.if ${MACHINE} == "atari" || ${MACHINE} == "amiga"
PROG=iteconfig
CPPFLAGS+=-I${NETBSDSRCDIR}/sys/arch -D${MACHINE}
.endif

MAN=	iteconfig.8

.include <bsd.prog.mk>
