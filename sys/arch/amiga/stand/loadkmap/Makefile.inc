# $NetBSD$

BINDIR=/usr/share/keymaps/amiga
NOMAN=	# defined
CLEANFILES=${FILES}

realall: ${HOSTPROG} ${FILES}

${FILES}: ${HOSTPROG}
	./${HOSTPROG} > $@
