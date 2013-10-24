#	$NetBSD$

PROG=	msgfmt

.include <bsd.prog.mk>
.include "${.CURDIR}/../Makefile.inc.prog"

CPPFLAGS+=-I${DIST}/gettext/gettext-runtime/intl

CWARNFLAGS.clang+=	-Wno-format-extra-args
