# $NetBSD$

.include <bsd.own.mk>

PROG=	progress
SRCS=	progress.c progressbar.c

CPPFLAGS+=-I${NETBSDSRCDIR}/usr.bin/ftp -DSTANDALONE_PROGRESS

.PATH:	${NETBSDSRCDIR}/usr.bin/ftp

.include <bsd.prog.mk>
