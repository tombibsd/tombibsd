#	$NetBSD$

.include <bsd.own.mk>

SUBDIR=	README_FILES html

.if ${MKSHARE} != "no" || \
	make(clean) || make(cleandir) || make(distclean) || make(obj)
SUBDIR+=conf
.endif


.include <bsd.subdir.mk>
