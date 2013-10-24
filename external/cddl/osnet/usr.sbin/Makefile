#	$NetBSD$

.include <bsd.own.mk>

.if ${MKDTRACE} != "no"
SUBDIR+=	dtrace
.endif

.if ${MKZFS} != "no"
SUBDIR+=	zdb
.endif

.include <bsd.subdir.mk>
