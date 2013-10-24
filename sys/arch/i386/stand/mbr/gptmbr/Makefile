#	$NetBSD$

PROG=		gptmbr.bin
SRCS=		gptmbr.S

AFLAGS.gptmbr.S= ${${ACTIVE_CC} == "clang":?-no-integrated-as:}

.include <../Makefile.mbr>

LOADADDR=	0x600
