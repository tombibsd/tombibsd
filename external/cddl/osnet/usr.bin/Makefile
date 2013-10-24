#	$NetBSD$

.include <bsd.own.mk>

.if ${MKDTRACE} != "no"
SUBDIR+=	ctfconvert ctfmerge ctfdump
.endif

.if ${MKZFS} != "no"
SUBDIR+=	ztest
.endif

.include <bsd.subdir.mk>
