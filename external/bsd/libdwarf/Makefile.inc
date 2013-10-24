#	$NetBSD$

.include <bsd.own.mk>

LIBDWARF_DIR=	${NETBSDSRCDIR}/external/bsd/libdwarf/dist

CPPFLAGS+=	-I${LIBDWARF_DIR}

WARNS?=		4

.PATH:		${LIBDWARF_DIR}
