# $NetBSD$
# Original from FreeBSD, no rcs id

PROG= pkg_info
SRCS= main.c perform.c show.c

.include <bsd.init.mk>

.PATH:	${DIST}/info

CWARNFLAGS.clang+=	-Wno-format-security

.include <bsd.prog.mk>
