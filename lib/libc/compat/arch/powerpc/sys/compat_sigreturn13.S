/*	$NetBSD$	*/

#include "SYS.h"

WARN_REFERENCES(sigreturn, \
    "warning: reference to compatibility sigreturn()")

PSEUDO(sigreturn,compat_13_sigreturn13)
