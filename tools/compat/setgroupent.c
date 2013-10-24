/*	$NetBSD$	*/

#include "nbtool_config.h"

#if !HAVE_SETGROUPENT || !HAVE_DECL_SETGROUPENT
#include <grp.h>

int setgroupent(int stayopen) {
	setgrent();
	return 1;
}
#endif
