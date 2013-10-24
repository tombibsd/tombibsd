#	$NetBSD$

NOMAN=		# defined
LDSTATIC=	-static

PROG=		getcwd
SRCS=		getcwd.c old_getcwd.c
WARNS=		1

regress: ${PROG}
	@./getcwd -r
	@./getcwd -p

long-regress:
	@find /usr -type d -print | ./getcwd -s

.include <bsd.prog.mk>
