#       $NetBSD$

.include <bsd.own.mk>

PROG=	lzf
MAN=	lzf.1
SRCS=	lzf.c

LINKS+=	${BINDIR}/lzf ${BINDIR}/unlzf \
	${BINDIR}/lzf ${BINDIR}/lzfcat

MLINKS+= lzf.1 unlzf.1 \
	 lzf.1 lzfcat.1

LDADD=	-llzf

.include "${.CURDIR}/../Makefile.inc"

.include <bsd.prog.mk>
