#!/bin/sh -
#
#	$NetBSD$
#	from: @(#)slip.login	8.1 (Berkeley) 6/6/93

#
# generic login file for a slip line.  sliplogin invokes this with
# the parameters:
#      1        2         3        4          5         6     7-n
#   slipunit ttyspeed loginname local-addr remote-addr mask opt-args
#
UNIT=$1
LOCALADDR=$4
REMOTEADDR=$5
NETMASK=$6
shift 6
OPTARGS=$*

/sbin/ifconfig sl${UNIT} inet ${LOCALADDR} ${REMOTEADDR} netmask ${NETMASK} \
    ${OPTARGS}
exit
