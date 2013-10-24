#	$NetBSD$

NOMAN=		# defined

PROG=		softint1

LDADD+=		-lpthread
DPADD+=		${LIBPTHREAD}

regress:
	@./${PROG}

.include <bsd.prog.mk>
