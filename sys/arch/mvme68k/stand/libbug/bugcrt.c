/*	$NetBSD$	*/

#include <sys/types.h>
#include <machine/prom.h>

#include <lib/libsa/stand.h>

#include "libbug.h"

void
_bugstart(void)
{
	extern int main(void);
	struct mvmeprom_brdid *id;

	/*
	 * Be sure not to de-reference NULL
	 */
	if (bugargs.arg_end != NULL)
		*bugargs.arg_end = 0;

	id = mvmeprom_getbrdid();
	bugargs.cputyp = id->model;
	(void)main();
	_rtt();
	/* NOTREACHED */
}
