# $NetBSD$
#
# Generic Alpha kernel with multiprocessor support.

include	"arch/alpha/conf/GENERIC"

options 	MULTIPROCESSOR		# include multiprocessor support

makeoptions	DEBUG="-g"		# ...and full symbols
