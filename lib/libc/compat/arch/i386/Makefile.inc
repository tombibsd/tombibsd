#	$NetBSD$

.include "${COMPATARCHDIR}/gen/Makefile.inc"
.if ${RUMPRUN} != "yes"
.include "${COMPATARCHDIR}/sys/Makefile.inc"
.endif
