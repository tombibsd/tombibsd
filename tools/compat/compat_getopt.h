/*      $NetBSD$ */

/* We unconditionally use the NetBSD getopt.h in libnbcompat. */

#if HAVE_GETOPT_H
#include <getopt.h>
#endif

#define option __nbcompat_option
#define getopt_long __nbcompat_getopt_long

#undef no_argument
#undef required_argument
#undef optional_argument
#undef _GETOPT_H_

#include "../../include/getopt.h"
