/* $NetBSD$ */

/*
 *	files.c:
 *
 *	libsa file table.  separate from other global variables so that
 *	all of those don't need to be linked in just to use open, et al.
 */

#include "stand.h"

struct open_file files[SOPEN_MAX];
