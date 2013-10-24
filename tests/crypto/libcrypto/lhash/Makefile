# $NetBSD$

HELPER_NAME=	lhashtest
HELPER_DIR=	lhash
HELPER_SRCS=	lh_test.c

CPPFLAGS+=	-DMalloc=malloc
DPADD+=		${LIBCRYPTO} ${LIBCRYPT}

.include <bsd.init.mk>
