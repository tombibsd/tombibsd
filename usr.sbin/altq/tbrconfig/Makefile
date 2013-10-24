#	$NetBSD$

.include <bsd.own.mk>		# for MKDYNAMICROOT definition

PROG=	tbrconfig
MAN=	tbrconfig.8

BINDIR=	/sbin
.if (${MKDYNAMICROOT} == "no")
LDSTATIC?=-static
.endif

CPPFLAGS+= -DALTQ -I${.CURDIR}/../libaltq

.include <bsd.prog.mk>
