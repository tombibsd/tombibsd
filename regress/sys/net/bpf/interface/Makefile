#	$NetBSD$

NOMAN=	# defined

PROG=	interface
WARNS=	3

regress:
	@if ./${PROG} ; then		\
		echo "PASSED";		\
	else				\
		echo "FAILED";		\
	fi

.include <bsd.prog.mk>
