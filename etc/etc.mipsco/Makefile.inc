#	$NetBSD$
#
#	etc.mipsco/Makefile.inc -- mipsco-specific etc Makefile targets
#

# If you change the list of distributed kernels, don't forget
# to update the release documentation in distrib/notes/common/contents

KERNEL_SETS=		GENERIC

BUILD_KERNELS=		RAMDISK

INSTALLATION_DIRS+=	installation/diskimage	\
			installation/netboot
