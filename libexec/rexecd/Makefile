#	$NetBSD$
#	from @(#)Makefile	8.1 (Berkeley) 6/4/93

.include <bsd.own.mk>

PROG=	rexecd
MAN=	rexecd.8

.if ${USE_PAM} != "no"

CPPFLAGS+= -DUSE_PAM -DPAM_DEBUG
LDADD+= -lpam ${PAM_STATIC_LDADD}
DPADD+=	${LIBPAM} ${PAM_STATIC_DPADD}

.else

LDADD+= -lcrypt
DPADD+= ${LIBCRYPT}

.endif

.include <bsd.prog.mk>
