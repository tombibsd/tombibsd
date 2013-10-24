#	$NetBSD$

.include <bsd.own.mk>

CPPSCRIPTS=	ccmakedep
CPPSCRIPTFLAGS=	-DPREPROC='"gcc -E -traditional"'
SCRIPTS=	${CPPSCRIPTS}
MAN=		ccmakedep.1

BUILDSYMLINKS=	mdepend.cpp ccmakedep.cpp

.PATH:	${X11SRCDIR.imake}

.include <bsd.x11.mk>
.include <bsd.prog.mk>
