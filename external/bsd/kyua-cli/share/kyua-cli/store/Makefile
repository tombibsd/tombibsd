# $NetBSD$

.include <bsd.init.mk>

.if ${MKSHARE} != "no"
.PATH:		${SRCDIR}/store

FILESDIR=	${KYUA_STOREDIR}
FILESMODE=	444
FILES=		migrate_v1_v2.sql \
		schema_v2.sql
.endif

.include <bsd.files.mk>
