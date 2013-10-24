# $NetBSD$

MODULE=	savage

SRCS=	savage_xmesa.c savagedd.c savagestate.c savagetex.c savagetris.c \
	savagerender.c savageioctl.c savagespan.c

CWARNFLAGS.clang+=	-Wno-constant-logical-operand -Wno-error

.include "${.CURDIR}/../dri.mk"
