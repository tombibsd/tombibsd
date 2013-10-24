#	$NetBSD$

LIBISPRIVATE=	yes

.if !empty(LIB:Mlldb*)
CPPFLAGS+=	-I${LLDB_SRCDIR}/source
CPPFLAGS+=	-I${LLDB_SRCDIR}/source/Plugins/Process/POSIX
.endif

.include "${.PARSEDIR}/../Makefile.inc"
