#	$NetBSD$

.include <bsd.own.mk>

DIST=		${NETBSDSRCDIR}/gnu/dist

CPPFLAGS+=	-DHAVE_CONFIG_H -I${.CURDIR} -I${.CURDIR}/../include \
		-I${DIST}/gettext/gettext-tools/lib -DLOCALEDIR=\"/usr/share/locale\"

BINDIR?=	/usr/bin

CWARNFLAGS.clang+=	-Wno-format-security
