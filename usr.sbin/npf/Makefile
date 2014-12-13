# $NetBSD$

.include <bsd.own.mk>

SUBDIR=		npfctl

.if ${MKRUMP} != "no" && ${MKPIC} != "no"
SUBDIR+=	npftest
.endif

MAN=		npf.7

.include <bsd.man.mk>
.include <bsd.subdir.mk>
