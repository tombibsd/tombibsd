#	$NetBSD$

.include <bsd.own.mk>

DIST= ${NETBSDSRCDIR}/dist/nvi
.PATH: ${DIST}

CWARNFLAGS.clang+=	-Wno-error=unused-const-variable
