#	$NetBSD$

.include <bsd.own.mk>

USE_FORT?= yes	# data driven bugs?

DIST=		${NETBSDSRCDIR}/gnu/dist/gkermit

PROG=		gkermit
SRCS=		gcmdline.c gkermit.c gproto.c gunixio.c
MAN=		gkermit.1

# Note that we do not use gwart.  Provided gproto.w is unchanged,
# the distributed gproto.c does not need to be updated.

BUILDSYMLINKS+=	gkermit.nr gkermit.1

CPPFLAGS+=	-DPOSIX
CPPFLAGS+=	-I${DIST}

CWARNFLAGS.clang+=	-Wno-unused-value

.PATH: ${DIST}

.include <bsd.prog.mk>
