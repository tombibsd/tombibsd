#	$NetBSD$

.include <bsd.own.mk>

PROG=	xmessage
SRCS=	xmessage.c makeform.c readfile.c

APPDEFS=Xmessage.ad Xmessage-color.ad

LDADD+=	-lXaw -lXmu -lXt -lSM -lICE -lXpm -lXext -lX11
DPADD+=	${LIBXAW} ${LIBXMU} ${LIBXT} ${LIBSM} ${LIBICE} \
	${LIBXPM} ${LIBXEXT} ${LIBX11}

CPPFLAGS+=-DHAS_MKSTEMP

.PATH:	${X11SRCDIR.xc}/programs/${PROG}

.include <bsd.x11.mk>
.include <bsd.prog.mk>
