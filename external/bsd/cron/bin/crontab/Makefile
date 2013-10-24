#	$NetBSD$

.include <bsd.own.mk>

USE_FORT?= yes	# setuid
PROG=	crontab
SRCS=	crontab.c misc.c entry.c env.c pw_dup.c
CPPFLAGS+=-I${.CURDIR} -DDEBUGGING=1
BINOWN =root
BINMODE=4555
BINDIR=/usr/bin
MAN=	crontab.1 crontab.5

.include <bsd.prog.mk>
