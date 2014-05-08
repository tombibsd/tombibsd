# $NetBSD$

.include <bsd.own.mk>

FILESDIR=/usr/lib/pkgconfig
.for pkg in ${PKGCONFIG}
FILES+=${pkg}.pc
FILESBUILD_${pkg}.pc=yes

${pkg}.pc: ${.CURDIR}/../../mkpc
	${HOST_SH} ${.ALLSRC} ${OPENSSLSRC}/crypto ${.TARGET} > ${.TARGET}
.endfor
