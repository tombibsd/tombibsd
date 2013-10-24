/*	$NetBSD$	*/

#include "nbtool_config.h"

#if !HAVE_SETPASSENT || !HAVE_DECL_SETPASSENT
#include <pwd.h>

int setpassent(int stayopen) {
	setpwent();
	return 1;
}
#endif
