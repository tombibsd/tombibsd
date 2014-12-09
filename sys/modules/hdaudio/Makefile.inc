#	$NetBSD$

# This file is used by modules and rump kernels

IOCONFDIR:=	${.PARSEDIR}

.PATH:	${NETBSDSRCDIR}/sys/dev/pci/hdaudio ${IOCONFDIR}

IOCONF=	hdaudio.ioconf
SRCS=	hdaudio.c
SRCS+=	hdaudio_pci.c
