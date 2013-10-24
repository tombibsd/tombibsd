#	$NetBSD$

PROG=	mlxctl
SRCS=	cmds.c config.c dklist.c main.c util.c
MAN=	mlxctl.8

LDADD=	-lkvm
DPADD=	${LIBKVM}

.include <bsd.prog.mk>
