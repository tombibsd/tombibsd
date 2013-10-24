#	$NetBSD$

.include <bsd.own.mk>

LIBELF_DIR=	${NETBSDSRCDIR}/external/bsd/libelf/dist

CPPFLAGS+=	-I${LIBELF_DIR}

WARNS?=		4

.PATH:		${LIBELF_DIR}
