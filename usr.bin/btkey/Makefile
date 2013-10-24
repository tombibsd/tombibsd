# $NetBSD$

PROG=	btkey
SRCS=	btkey.c device.c file.c
MAN=	btkey.1

DPADD+=	${LIBBLUETOOTH} ${LIBPROP}
LDADD+=	-lbluetooth -lprop

.include <bsd.prog.mk>
