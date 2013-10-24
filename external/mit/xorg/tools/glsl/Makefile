#	$NetBSD$

NOMAN=	1

.include <bsd.own.mk>

.PATH:	${X11SRCDIR.MesaLib}/src/glsl/apps

.include "Makefile.glslsrcs"

HOSTPROG=	glsl-compile

SRCS=	compile.c

SRCS+=	${SRCS.pp} ${SRCS.cl}

# also: process.c purify.c tokenise.c version.c

.include <bsd.hostprog.mk>
