#	$NetBSD$
#	@(#)Makefile	8.1 (Berkeley) 6/6/93

.include <bsd.own.mk>

PROG=	lpd
MAN=	lpd.8
SRCS=	lpd.c printjob.c recvjob.c lpdchar.c key.c modes.c ttcompat.c rcmd.c

CPPFLAGS+=-DLIBWRAP
LDADD+=	-lwrap
DPADD+=	${LIBWRAP}

.if (${USE_INET6} != "no")
CPPFLAGS.rcmd.c=	-DINET6
.endif

.PATH:	${NETBSDSRCDIR}/lib/libc/net

.include <bsd.prog.mk>
