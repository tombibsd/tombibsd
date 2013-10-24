#	$NetBSD$

.include <bsd.own.mk>

PROG=	utoppya
SRCS=	utoppya.c progressbar.c

CPPFLAGS+=-I${NETBSDSRCDIR}/usr.bin/ftp -DSTANDALONE_PROGRESS

.PATH:	${NETBSDSRCDIR}/usr.bin/ftp

.include <bsd.prog.mk>
