#	$NetBSD$

# list of subdirs used per-platform

.if ${MACHINE} == "amd64" || ${MACHINE} == "i386"
# not yet
#ARCHDIR_SUBDIR=	x86/x86-xen
.endif

.if ${MACHINE_ARCH} == "powerpc"
ARCHDIR_SUBDIR=	powerpc/powerpc-4xx powerpc/powerpc-booke
.endif
