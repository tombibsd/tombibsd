#	$NetBSD$

PROG=	midirecord

.include <bsd.own.mk>

LIBAUDIO != cd ${.CURDIR}/../audio/common && ${PRINTOBJDIR}
CPPFLAGS+=-I${.CURDIR}/../audio/common
DPADD+=	${LIBAUDIO}/libaudio.a
LDADD+=	-L${LIBAUDIO} -laudio

DPADD+=	${LIBUTIL}
LDADD+=	-lutil

.include <bsd.prog.mk>
