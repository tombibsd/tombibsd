#	$NetBSD$

NOMAN=	#defined

.include <bsd.own.mk>	# ACTIVE_CC

PROG=	ras2

regress:
	@if ./${PROG} ; then		\
		echo "PASSED";		\
	else				\
		echo "FAILED";		\
	fi

CFLAGS+=	${${ACTIVE_CC} == "gcc":? -fno-reorder-blocks :}

.include <bsd.prog.mk>
