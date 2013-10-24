#   $NetBSD$

.include <bsd.own.mk>

.if ${MACHINE} == "amiga"
PROG=		grfconfig
CPPFLAGS+=	-I${NETBSDSRCDIR}/sys/arch -D${MACHINE}
.endif

MAN=		grfconfig.8
MANSUBDIR=	/amiga

.include <bsd.prog.mk>
