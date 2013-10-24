# $NetBSD$

.include <bsd.own.mk>
.include <${.CURDIR}/../../Makefile.inc>

.PATH: ${HEIMDIST}/lib/kadm5

PROG= iprop-log
MAN=  iprop-log.8

HEIMSRCS= iprop-log.c iprop-commands.in

CPPFLAGS+= -I${DESTDIR}/usr/include/kadm5

LDADD+= -lkadm5srv -lhdb -lsl
LDADD+= -ledit -lterminfo
DPADD+= ${LIBKADM5SRV} ${LIBHDB} ${LIBSL}
DPADD+= ${LIBEDIT} ${LIBTERMINFO}

.include <${HEIMBASE}/Makefile.rules.inc>
.include <bsd.prog.mk>
