#	$NetBSD$

.include <bsd.own.mk>

DISKLABELPATH=	${NETBSDSRCDIR}/sbin/disklabel
PROG=	svhlabel
SRCS=	svhlabel.c dkcksum.c printlabel.c
CPPFLAGS+= -I${DISKLABELPATH}
MAN=	svhlabel.8
LDADD+=	-lutil

.PATH:	${DISKLABELPATH} ${NETBSDSRCDIR}/sys/lib/libkern
.include <bsd.prog.mk>
