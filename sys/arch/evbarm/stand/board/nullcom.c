/*	$NetBSD$	*/

/* 
 * nulldev-like console stubs for quiet gzboot
 */
#include <lib/libsa/stand.h>
#include "board.h"

void
cons_init(void)
{
}

int
getchar(void)
{
	return 0;	/* XXX */
}

void
putchar(int c)
{
}
