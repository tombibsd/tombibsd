#	$NetBSD$
#

.include <bsd.own.mk>

MOUNTNAME=	nfs

SRCS+=		getnfsargs.c
LDADD+= 	-lrumpfs_nfs -lrumpnet -lrumpnet_sockin

ISRUMP=		# gives me nightmares
#CPPFLAGS+=	-DINET6 # for getnfsargs?

.include <bsd.prog.mk>
