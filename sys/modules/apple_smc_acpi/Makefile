# $NetBSD$

.include "../Makefile.inc"

.PATH:	${S}/dev/acpi

KMOD=	apple_smc_acpi
IOCONF=	apple_smc_acpi.ioconf
SRCS=	apple_smc_acpi.c

WARNS=	4

CPPFLAGS+=	-DDIAGNOSTIC

.include <bsd.kmodule.mk>
