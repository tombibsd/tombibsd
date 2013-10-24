#	$NetBSD$
#

.include "../Makefile.inc"

.PATH:	${S}/net

KMOD=	bpfjit
SRCS=	bpfjit.c

CPPFLAGS+=	\
	-I ${NETBSDSRCDIR}/sys/external/bsd/sljit/dist/sljit_src

.include <bsd.kmodule.mk>
