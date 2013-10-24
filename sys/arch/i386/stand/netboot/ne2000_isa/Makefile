#	$NetBSD$

USE_NETIF=	ne2000_isa

CPPFLAGS+= -DBASEREG=0x300

.include "../Makefile.netboot"

COPTS.dp8390.c +=	-Wno-pointer-sign

