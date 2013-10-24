/*	$NetBSD$	*/

#include "SYS.h"

WARN_REFERENCES(sigaction, \
    "warning: reference to compatibility sigaction(); include <signal.h> for correct reference")

PSEUDO(sigaction,compat_13_sigaction13)
