# $NetBSD$

.include <bsd.own.mk>
.include <${.CURDIR}/../../Makefile.inc>

.PATH: ${HEIMDIST}/kuser

PROG= kdigest
# no man-page yet
MAN=

HEIMSRCS+= kdigest.c kdigest-commands.in

LDADD+= -lheimntlm -lsl -lutil -ledit -lterminfo
DPADD+= ${LIBHEIMNTLM} ${LIBSL} ${LIBUTIL} ${LIBEDIT} ${LIBTERMINFO}

.include <${HEIMBASE}/Makefile.rules.inc>
.include <bsd.prog.mk>
