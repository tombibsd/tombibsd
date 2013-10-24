# $NetBSD$

NOMAN=	#
PROG=	tramptest
LDADD=	-lpthread

UNSUPPORTED_COMPILER.clang=
UNSUPPORTED_COMPILER.pcc=

regress: ${PROG}
	@if ./tramptest; then \
		echo "PASSED"; \
	else \
		echo "FAILED"; \
	fi

.include <bsd.prog.mk>
