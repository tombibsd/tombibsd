#	$NetBSD$

.include <bsd.own.mk>

.if ${MKPIC} != "no"
# No support for shared libraries and pic code.
SUBDIR+=	gpio sqlite syslog
.endif

.include <bsd.subdir.mk>
