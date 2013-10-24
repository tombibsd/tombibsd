# $NetBSD$

.PATH: ${.CURDIR}/DEC

CODE:=		DEC
SEP_DEC:=
.include "${.CURDIR}/Makefile.part"

.for i in ${DEC_PART}
.if !exists(${.CURDIR}/DEC/DEC${i:S/:/@/}.src)
DEC${i:S/:/@/}.src: DEC.src
	${_MKTARGET_CREATE}
	${TOOL_SED} 's/DECx/DEC$i/' $> > $@
CLEANFILES+=	DEC${i:S/:/@/}.src
.endif
.endfor
