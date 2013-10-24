#	$NetBSD$

PROG=		install-info
SRCS=		install-info.c

.include <bsd.prog.mk>

.PATH: ${IDIST}/util ${IDIST}/doc

infodir-meta:
.if (${MKUNPRIVED} != "no" && ${MKINFO} != "no")
	echo "./usr/share/info/dir type=file mode=0644 uname=${BINOWN} gname=${BINGRP}" \
	    | ${METALOG.add}
.endif
