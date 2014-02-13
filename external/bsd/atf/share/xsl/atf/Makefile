# $NetBSD$

.include <bsd.own.mk>

.if ${MKSHARE} != "no"
SRCDIR=		${NETBSDSRCDIR}/external/bsd/atf/dist
.PATH:		${SRCDIR}/tools

FILESDIR=	/usr/share/xsl/atf
FILESMODE=	444
FILES=		tests-results.xsl
.endif

.include <bsd.prog.mk>
