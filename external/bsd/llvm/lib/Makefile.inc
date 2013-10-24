#	$NetBSD$

LIBISPRIVATE=	yes

.if !empty(LIB:Mlldb*)
CPPFLAGS+=	-I${LLDB_SRCDIR}/source
.endif

.include "${.PARSEDIR}/../Makefile.inc"
