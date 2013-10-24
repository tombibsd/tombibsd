#	$NetBSD$

NOMAN=		# defined

PROG=		select
WARNS?=		4

LDADD=		-lpthread

regress:
	@if ${.OBJDIR}/select 5; then \
		echo "PASSED"; \
	else \
		echo "FAILED"; \
	fi

.include <bsd.prog.mk>
