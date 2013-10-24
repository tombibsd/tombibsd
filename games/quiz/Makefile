#	$NetBSD$
#	@(#)Makefile	8.1 (Berkeley) 5/31/93

.include <bsd.own.mk>

PROG=	quiz
MAN=	quiz.6
SRCS=	quiz.c rxp.c
HIDEGAME=hidegame
.if ${MKSHARE} != "no"
CATS=	africa america areas arith asia babies bard chinese collectives \
	ed elements europe flowers greek inca index latin locomotive \
	midearth morse mult murders poetry posneg pres province seq-easy \
	seq-hard sexes sov spell state trek ucc
FILES= ${CATS:S@^@${.CURDIR}/datfiles/@}
FILESDIR=/usr/share/games/quiz.db
.endif

.include <bsd.prog.mk>
