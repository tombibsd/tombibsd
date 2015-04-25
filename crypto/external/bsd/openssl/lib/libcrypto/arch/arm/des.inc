#	$NetBSD$

.PATH.S: ${.PARSEDIR}
CPPFLAGS+=	-DDES_INT -DDES_UNROLL
.include "${.CURDIR}/des.inc"
