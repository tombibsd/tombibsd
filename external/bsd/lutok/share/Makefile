# $NetBSD$

.include <bsd.own.mk>

.if ${MKSHARE} != "no" || \
	make(clean) || make(cleandir) || make(distclean) || make(obj)
SUBDIR= examples
.endif

.include <bsd.subdir.mk>
