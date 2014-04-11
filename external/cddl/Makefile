#	$NetBSD$
.include <bsd.own.mk>

# We need more modular flag e.g. we can add dtrace to osnet later

.if ( ${MKZFS} != "no" || ${MKDTRACE} != "no" || ${MKCTF} != "no")
SUBDIR+= osnet
.endif

.include <bsd.subdir.mk>

