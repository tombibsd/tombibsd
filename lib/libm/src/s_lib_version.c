/* @(#)s_lib_ver.c 5.1 93/09/24 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#include <sys/cdefs.h>
#if defined(LIBM_SCCS) && !defined(lint)
__RCSID("$NetBSD$");
#endif

/*
 * MACRO for standards
 */

#include "math.h"
#include "math_private.h"

/*
 * define and initialize _LIB_VERSION
 */
#ifdef _POSIX_MODE
_LIB_VERSION_TYPE _LIB_VERSION = _POSIX_;
#else
#ifdef _XOPEN_MODE
_LIB_VERSION_TYPE _LIB_VERSION = _XOPEN_;
#else
#ifdef _SVID3_MODE
_LIB_VERSION_TYPE _LIB_VERSION = _SVID_;
#else					/* default _IEEE_MODE */
_LIB_VERSION_TYPE _LIB_VERSION = _IEEE_;
#endif
#endif
#endif
