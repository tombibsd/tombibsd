#	$NetBSD$

ROG_CXX=	machdo-dumpx
NOMAN=		yes

.include <bsd.init.mk>

.PATH: ${LLVM_SRCDIR}/tools/macho-dump

SRCS=	macho-dump.cpp

LLVM_LIBS+= \
	Object \
	IR \
	Support

.include "${.PARSEDIR}/../../link.mk"

.include <bsd.prog.mk>
