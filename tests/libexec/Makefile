# $NetBSD$
#
.include "Makefile.inc"
.include <bsd.own.mk>

.if ${MACHINE_ARCH} != "m68000"
TESTS_SUBDIRS=		ld.elf_so
.endif

TESTSDIR=	${TESTSBASE}/libexec

.include <bsd.test.mk>
