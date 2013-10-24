# $NetBSD$
#
#	P2020RDB kernel, plus multiprocessor support.

include	"arch/evbppc/conf/P2020RDB"

options 	MULTIPROCESSOR
# this option may cause trouble under very high interrupt load
#options 	OPENPIC_DISTRIBUTE	# let all CPUs serve interrupts
