#	$NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/dev/pci/hdaudio

KMOD=	hdaudio
IOCONF=	hdaudio.ioconf
SRCS=	hdaudio.c
SRCS+=	hdaudio_ids.c
SRCS+=	hdaudio_pci.c

.include <bsd.kmodule.mk>
