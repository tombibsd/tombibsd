#	$NetBSD$

.include <bsd.own.mk>

SUBDIR=	cf
.if ${MKSHARE} != "no" || \
	make(clean) || make(cleandir) || make(distclean) || make(obj)
SUBDIR+=fonts man nls
.endif

.include <bsd.subdir.mk>
