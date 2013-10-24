#	$NetBSD$

NOMAN=		# defined

PROG=		lint2
SRCS=		main2.c hash.c read.c mem.c mem2.c chk.c msg.c emit.c emit2.c \
		inittyp.c tyname.c
LINTFLAGS=	-abehrz
BINDIR=		/usr/libexec
CPPFLAGS+=	-DPASS=\"${PROG}.h\" -I${.CURDIR}

.include <bsd.prog.mk>
