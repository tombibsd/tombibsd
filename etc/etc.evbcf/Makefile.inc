#	$NetBSD$
#
#	etc.evbcf/Makefile.inc -- evbcf-specific etc Makefile targets
#

# If you change the list of distributed kernels, don't forget
# to update the release documentation in distrib/notes/common/contents

KERNEL_SETS=		TWR54418

BUILD_KERNELS=		TWR54418_INSTALL

snap_md_post:
