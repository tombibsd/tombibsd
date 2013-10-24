# $NetBSD$

.include <bsd.own.mk>

# XXX documentation (BTW, agc@ started writing a manual page)
NOMAN=		# defined

LIB=		sljit

# Keep sljit private for the time being because it's
# still under active development and API can change.
LIBISPRIVATE=	yes

SLJITDIST=	${NETBSDSRCDIR}/sys/external/bsd/sljit/dist
.PATH:		${SLJITDIST}/sljit_src

SRCS=		sljitLir.c

.include <bsd.lib.mk>
