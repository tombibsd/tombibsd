#	$NetBSD$

NOMAN=		# defined

PROG=		ioperm
WARNS=		4
DPADD+=		${LIBARCH}
LDADD+=		-li386

regress:
	-@if ./${PROG}; \
	then echo PASSED; \
	else echo FAILED; fi

.include <bsd.prog.mk>
