#	$NetBSD$

SRCDIR=		${.CURDIR}/../../../usr.bin/netstat

PROG=		netstat
NOMAN=		# defined

SRCS=		if.c inet.c main.c mbuf.c route.c

CPPFLAGS+=	-DSMALL -I${SRCDIR} -DCRUNCHOPS
DPADD=		${LIBKVM}
LDADD=		-lkvm

.include <bsd.prog.mk>

BINOWN=		root
BINMODE=	4555
.PATH:		${SRCDIR}
