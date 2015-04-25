#	$NetBSD$

.include <bsd.own.mk>

SUBDIR+=	expat lua

.if ${MKX11} != "no" && ${X11FLAVOUR} == "Xorg"
SUBDIR+=	xorg
.endif

.include <bsd.subdir.mk>
