/*	$NetBSD$	*/

#include <sys/types.h>
#include <machine/prom.h>

#include <lib/libsa/stand.h>
#include <ufs.h>
#include "libsa.h"

struct fs_ops file_system[] = {
	FS_OPS(ufs),
};
int nfsys = __arraycount(file_system);

struct devsw devsw[] = {
        { "bugsc", bugscstrategy, bugscopen, bugscclose, bugscioctl },
};
int     ndevs = __arraycount(devsw);
