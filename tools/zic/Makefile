#	$NetBSD$

HOSTPROGNAME=	${_TOOL_PREFIX}zic
HOST_SRCDIR=	usr.sbin/zic

.if !empty(HOST_OSTYPE:MSunOS-5.1[01]-*)
HOST_CPPFLAGS=	-D_POSIX_PTHREAD_SEMANTICS
.endif

.include "${.CURDIR}/../Makefile.host"
