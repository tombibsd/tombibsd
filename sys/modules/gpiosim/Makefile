#	$NetBSD$

.include "../Makefile.inc"

.PATH:		${S}/dev/gpio

KMOD=   	gpiosim
SRCS=		gpiosim.c

CPPFLAGS+=	-I${S}/gpio

.include <bsd.kmodule.mk>
