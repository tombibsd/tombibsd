#	$NetBSD$

PROG= lastlogin
MAN= lastlogin.8
CPPFLAGS+=-DSUPPORT_UTMP -DSUPPORT_UTMPX

LDADD+=-lutil
DPADD+=${LIBUTIL}

.include <bsd.prog.mk>
