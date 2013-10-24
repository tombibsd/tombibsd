#	$NetBSD$

NOMAN=		# defined

PROG=		emuspeed
SRCS=		emuspeed.c test.S mul64.S div64.S # movepto.c movepfrom.c

.include <bsd.prog.mk>

regress: all
	@./emuspeed
