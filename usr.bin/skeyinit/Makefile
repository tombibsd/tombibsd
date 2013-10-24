#	$NetBSD$

.include <bsd.own.mk>

USE_FORT?= yes	# setuid
PROG= skeyinit
BINOWN=root
BINMODE=4555
CPPFLAGS+= -I${NETBSDSRCDIR}/lib/libskey
DPADD=	${LIBCRYPT} ${LIBSKEY}
LDADD=	-lcrypt -lskey

.include <bsd.prog.mk>
