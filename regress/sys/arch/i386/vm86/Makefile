# $NetBSD$

NOMAN=  	# defined

PROG=		vm86test
LDADD+=		-li386
CLEANFILES+=	vm86test.out

regress:
	./${PROG} 2>vm86test.out
	./${PROG} dummyarg 2>>vm86test.out
	tail +4 ${.CURDIR}/vm86test.exp | diff - vm86test.out

.include <bsd.prog.mk>
