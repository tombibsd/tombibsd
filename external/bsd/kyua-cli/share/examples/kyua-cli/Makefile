# $NetBSD$

.include <bsd.init.mk>

.if ${MKSHARE} != "no"
.PATH:		${SRCDIR}/examples

FILESDIR=	${KYUA_EXAMPLESDIR}
FILESMODE=	444
FILES=		Kyuafile.top kyua.conf
.endif

.include <bsd.files.mk>
