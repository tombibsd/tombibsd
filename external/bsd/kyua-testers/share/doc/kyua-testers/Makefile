# $NetBSD$

.include <bsd.init.mk>

SRCDIR=		${NETBSDSRCDIR}/external/bsd/kyua-testers/dist
.PATH:		${SRCDIR}

.if ${MKSHARE} != "no"
.PATH:		${SRCDIR}

FILESDIR=	/usr/share/doc/reference/ref1/kyua/kyua-testers
FILESMODE=	444
FILES=		AUTHORS COPYING NEWS README
.endif

.include <bsd.files.mk>
