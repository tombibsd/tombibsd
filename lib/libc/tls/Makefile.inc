#	$NetBSD$

.include <bsd.own.mk>

# Our sources
.PATH:	${.PARSEDIR} ${ARCHDIR}/tls

SRCS+=			tls.c
CPPFLAGS.tls.c+=	-D_LIBC_SOURCE
