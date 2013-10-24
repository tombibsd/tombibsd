#	$NetBSD$

.include <bsd.own.mk>

SUBDIR= kern fs uvm net
.if exists(arch/${MACHINE}/Makefile)
SUBDIR+= arch/${MACHINE}
.endif
.if exists(arch/${MACHINE_ARCH}/Makefile)
SUBDIR+= arch/${MACHINE_ARCH}
.endif
.if ${MKCRYPTO} != "no"
SUBDIR+=	crypto
.endif

SUBDIR := ${SUBDIR:O:u}

.include <bsd.subdir.mk>
