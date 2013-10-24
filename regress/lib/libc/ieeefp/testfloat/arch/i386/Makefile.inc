# $NetBSD$

CFLAGS+=	-ffloat-store -DFLOATX80 ## -DLONG_DOUBLE_IS_FLOATX80

SRCS+=		systfloat.S systmodes.S
