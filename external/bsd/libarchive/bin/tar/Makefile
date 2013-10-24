# $NetBSD$

PROG=	tar
SRCS=	bsdtar.c cmdline.c getdate.c read.c subst.c tree.c util.c write.c

.include <bsd.init.mk>

.PATH:		${LIBARCHIVEDIR}/tar

CLEANFILES+=	tar.1

tar.1: ${LIBARCHIVEDIR}/tar/bsdtar.1
	${TOOL_CAT} ${LIBARCHIVEDIR}/tar/bsdtar.1 > $@

SYMLINKS+=${BINDIR}/tar /usr/bin/tar

COPTS.read.c += -Wno-format-nonliteral

.include <bsd.prog.mk>
