#	$NetBSD$

NOMAN=	#defined

PROG=	sa1
WARNS=	3

regress:
	@if ./${PROG} ; then		\
		echo "PASSED";		\
	else				\
		echo "FAILED";		\
	fi

.include <bsd.prog.mk>
