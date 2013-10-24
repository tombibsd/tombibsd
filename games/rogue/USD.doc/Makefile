#	$NetBSD$
#	@(#)Makefile	8.1 (Berkeley) 6/8/93

DIR=	usd/30.rogue
SRCS=	rogue.me
MACROS=	-me

paper.ps: ${SRCS}
	${TOOL_TBL} ${SRCS} | ${TOOL_ROFF_PS} ${MACROS} > ${.TARGET}

.include <bsd.doc.mk>
