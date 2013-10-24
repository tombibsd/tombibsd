#	$NetBSD$

.include <bsd.x11.mk>

.if defined(X11FLAGS.LOADABLE)
SUBDIR+=	afbmod
.else
SUBDIR+=	afb
.endif

.include <bsd.subdir.mk>

gaga:
	@echo ${SUBDIR}
