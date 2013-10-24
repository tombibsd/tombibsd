#	$NetBSD$

SRCS=	scsictl.c scsi_sense.c scsi_subr.c

PROG=	scsictl
MAN=	scsictl.8

LDADD+=	-lutil
DPADD+=	${LIBUTIL}

.include <bsd.prog.mk>
