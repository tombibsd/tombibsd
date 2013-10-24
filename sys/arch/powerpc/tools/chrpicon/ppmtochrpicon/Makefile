#       $NetBSD$

PROG=   ppmtochrpicon
NOMAN=# defined

PBMROOT=/usr/pkg

CPPFLAGS+= -I${.CURDIR}/.. -I${PBMROOT}/include
LDADD+=-Wl,-R${PBMROOT}/lib -L${PBMROOT}/lib -lnetpbm

.include <bsd.prog.mk>

