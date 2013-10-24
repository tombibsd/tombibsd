#	$NetBSD$

.include <bsd.own.mk>

SUBDIR+= libc

.if (${MACHINE_CPU} != "alpha" && \
     ${MACHINE_CPU} != "mips" && \
     ${MACHINE_CPU} != "hppa")
#SUBDIR+= libssp
.endif

.include <bsd.subdir.mk>
