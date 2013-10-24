# $NetBSD$

PROG=	audiocfg
SRCS=	audiodev.c drvctl.c dtmf.c
SRCS+=	main.c

LDADD+=	-lprop -lm
DPADD+=	$(LIBPROP) $(LIBM)

.include <bsd.prog.mk>
