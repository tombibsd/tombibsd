/*	$NetBSD$	*/

#include "SYS.h"

WARN_REFERENCES(msgctl, \
    "warning: reference to compatibility msgctl(); include <sys/msg.h> for correct reference")

PSEUDO(msgctl,compat_14_msgctl)
