#	$NetBSD$

# This file is used by modules and rump kernels 

IOCONFDIR:=	${.PARSEDIR}
.PATH:	${NETBSDSRCDIR}/sys/dev/hdaudio ${IOCONFDIR}

IOCONF=	hdafg.ioconf
SRCS=	hdafg.c hdafg_dd.c
