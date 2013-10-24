/* $NetBSD$ */

/*
 * Written by Klaus Klein <kleink@NetBSD.org>, November 16, 2005.
 * Public domain.
 */

#include "gdtoaimp.h"

mutex_t __gdtoa_locks[2] = { MUTEX_INITIALIZER, MUTEX_INITIALIZER };
