#	$NetBSD$

.include "${.PARSEDIR}/../llvm/Makefile.inc"

HOSTLIB=	${LIB}

.include "${LLVM_TOPLEVEL}/lib/Makefile.inc"
.include "${LLVM_TOPLEVEL}/lib/${.CURDIR:T}/Makefile"

HOST_CPPFLAGS:=	${HOST_CPPFLAGS:N-Wp,-iremap,*}
