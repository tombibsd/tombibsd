# $NetBSD$

.include <bsd.own.mk>

.if ${MKSHARE} != "no"
SRCDIR=		${NETBSDSRCDIR}/external/bsd/atf/dist
.PATH:		${SRCDIR}/tools

FILESDIR=	/usr/share/xml/atf
FILESMODE=	444
FILES=		tests-results.dtd
.endif

.include <bsd.prog.mk>
