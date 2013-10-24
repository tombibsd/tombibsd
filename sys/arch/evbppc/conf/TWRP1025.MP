# $NetBSD$
#
#	TWRP1025 kernel, plus multiprocessor support.

include	"arch/evbppc/conf/TWRP1025"

options 	MULTIPROCESSOR
# this option may cause trouble under very high interrupt load
#options 	OPENPIC_DISTRIBUTE	# let all CPUs serve interrupts
