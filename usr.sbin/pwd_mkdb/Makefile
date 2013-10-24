#	from: @(#)Makefile	8.1 (Berkeley) 6/6/93
#	$NetBSD$

.include <bsd.own.mk>

PROG=	pwd_mkdb
MAN=	pwd_mkdb.8
CPPFLAGS+=	-I${NETBSDSRCDIR}/lib/libc/include

.ifndef HOSTPROG
LDADD+=	-lutil
DPADD+=	${LIBUTIL}
.endif

COPTS.pwd_mkdb.c+=	-Wno-format-nonliteral

.include <bsd.prog.mk>
