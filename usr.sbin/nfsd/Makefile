#	$NetBSD$
#	@(#)Makefile	8.1 (Berkeley) 6/5/93

USE_FORT?= yes	# network server

PROG=	nfsd
MAN=	nfsd.8

LDADD+= -lpthread
DPADD+= ${LIBPTHREAD}

.include <bsd.prog.mk>
