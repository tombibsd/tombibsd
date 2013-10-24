#	$NetBSD$
#
#	etc.sandpoint/Makefile.inc -- sandpoint-specific etc Makefile targets
#

# If you change the list of distributed kernels, don't forget
# to update the release documentation in distrib/notes/common/contents

KERNEL_SETS=		GENERIC KUROBOX
KERNEL_SUFFIXES=	srec

BUILD_KERNELS=  	INSTALL INSTALL_KURO
