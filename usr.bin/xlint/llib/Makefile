#	$NetBSD$

.include <bsd.own.mk>

LIBS=	llib-lposix.ln llib-lstdc.ln

.if ${MKLINT} != "no"
FILES=	${LIBS}
FILESDIR= ${LINTLIBDIR}

realall:	${LIBS}
.endif

CLEANFILES+= ${LIBS}

llib-lposix.ln: llib-lposix
	${_MKTARGET_CREATE}
	${LINT} ${LINTFLAGS} -Cposix ${.ALLSRC}

llib-lstdc.ln: llib-lstdc
	${_MKTARGET_CREATE}
	${LINT} ${LINTFLAGS} -Cstdc ${.ALLSRC}

.include <bsd.prog.mk>
