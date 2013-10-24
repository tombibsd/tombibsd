#	$NetBSD$

.if exists(${.CURDIR}/../../Makefile.inc)
.include "${.CURDIR}/../../Makefile.inc"
.endif

USE_FORT?=yes	# network server

# optional build configuration:
# I4B_WITHOUT_CURSES=1	# don't compile curses into the daemon
I4B_EXTERNAL_MONITOR=1	# enable local and remote monitoring of the daemon
# I4B_NOTCPIP_MONITOR=1	# for the security concious: isdn monitoring only via
#			# local domain socket, no TCP socket supported
