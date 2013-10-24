#	$NetBSD$

.include <bsd.own.mk>

.if ${MKX11FONTS} != "no"

SUBDIR=	encodings .WAIT \
	font-alias font-util \
	100dpi 75dpi Type1 TTF misc

.include "${NETBSDSRCDIR}/external/mit/xorg/tools/fc-cache/Makefile.fc-cache"

.endif

.include <bsd.subdir.mk>
