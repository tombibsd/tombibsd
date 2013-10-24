#	$NetBSD$

.include "${.CURDIR}/../../Makefile.inc"

DIST=	${IDIST}/contrib
.PATH:	${DIST} ${IDIST}/man

SCRIPTS=	rcs2log
MAN=		rcs2log.1
CLEANFILES=	${SCRIPTS}

rcs2log: rcs2log.sh
	sed -e "s/@MKTEMP_SH_FUNCTION@//" -e "s/@MKTEMP@/mktemp/" \
		${.ALLSRC} > ${.TARGET}

.include <bsd.prog.mk>
