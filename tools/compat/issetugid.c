/*	$NetBSD$	*/

/*
 * Written by Ben Harris, 2002
 * This file is in the Public Domain
 */

#include "nbtool_config.h"

#if !HAVE_ISSETUGID
int
issetugid(void)
{

	/*
	 * Assume that anything linked against libnbcompat will be installed
	 * without special privileges.
	 */
	return 0;
}
#endif
