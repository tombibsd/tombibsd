# $NetBSD$

.include <bsd.own.mk>

.include "${.PARSEDIR}/../Makefile.inc"

CPPFLAGS+=      -DMDNSD_NOROOT -DMDNSD_USER=\"_mdnsd\"

BINDIR?=	/usr/sbin
