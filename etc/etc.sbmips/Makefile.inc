# $NetBSD$
#
#	etc.sbmips/Makefile.inc -- sbmips-specific etc Makefile targets
#

# If you change the list of distributed kernels, don't forget
# to update the release documentation in distrib/notes/common/contents

KERNEL_SETS=		GENERIC${MACHINE_ARCH:S/mips//:C/e[lb]//}
