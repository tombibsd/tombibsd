# $NetBSD$

PROG=		btdevctl
MAN=		btdevctl.8
SRCS=		btdevctl.c db.c print.c sdp.c

DPADD+=		${LIBBLUETOOTH} ${LIBPROP} ${LIBUSBHID}
LDADD+=		-lbluetooth -lprop -lusbhid

.include <bsd.prog.mk>
