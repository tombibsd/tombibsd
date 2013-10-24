#	$NetBSD$

PROG=		ar

COPTS.arparse.c = -Wno-stack-protector
CPPFLAGS+=-Dbin_dummy_emulation=bin_vanilla_emulation

.include <bsd.own.mk>

.include "${.CURDIR}/../common/Makefile.prog"
