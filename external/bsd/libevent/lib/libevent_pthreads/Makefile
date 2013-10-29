#	$NetBSD$

LIB=event_pthreads

COPTS+=-pthread

SRCS=		evthread_pthread.c

LIBDPLIBS+= \
	event	${.CURDIR}/../libevent \
	pthread	${NETBSDSRCDIR}/lib/libpthread

.include <bsd.lib.mk>
