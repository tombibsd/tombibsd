#	$NetBSD$

USE_FORT?=	yes	# setgid
PROG=		pmap
SRCS=		main.c pmap.c
BINGRP=		kmem
BINMODE=	2555
LDADD=		-lkvm
DPADD=		${LIBKVM}

CWARNFLAGS.clang+=	-Wno-format-extra-args

.include <bsd.prog.mk>
