# $NetBSD$

MODULE=	swrast

CPPFLAGS+=	-I${X11SRCDIR.MesaLib}/src/mesa/drivers/dri/swrast

DRI_EXTRA_PATHS=	${X11SRCDIR.MesaLib}/src/mesa/drivers/dri/swrast
SRCS= \
	swrast.c \
        swrast_span.c

.include "${.CURDIR}/../dri.mk"
