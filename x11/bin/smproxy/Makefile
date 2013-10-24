#	$NetBSD$

.include <bsd.own.mk>

PROG=	smproxy
SRCS=	smproxy.c save.c

CPPFLAGS+=-DHAS_MKSTEMP

LDADD+=	-lXmu -lXt -lSM -lICE -lXext -lX11
DPADD+=	${LIBXMU} ${LIBXT} ${LIBSM} ${LIBICE} ${LIBXEXT} ${LIBX11}

.PATH:	${X11SRCDIR.xc}/programs/${PROG}

.include <bsd.x11.mk>
.include <bsd.prog.mk>
