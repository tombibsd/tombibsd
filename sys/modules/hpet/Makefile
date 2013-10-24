# $NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/dev/ic
.PATH:	${S}/dev/acpi
.PATH:	${S}/arch/x86/pci

KMOD=	hpet
IOCONF=	hpet.ioconf
SRCS=	hpet.c hpet_acpi.c amdpcib_hpet.c ichlpcib_hpet.c

WARNS=	4

.include <bsd.kmodule.mk>
