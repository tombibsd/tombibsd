/*	$NetBSD$	*/

/*
 * putchar: easier to do this with outstr than to add more macros to
 * handle byte passing on the stack
 */

#include <sys/types.h>
#include <machine/prom.h>

#include "stand.h"
#include "libbug.h"

void
putchar(int c)
{
	char ca[2];

	if (c == '\n')
		putchar('\r');
	ca[0] = c;
	mvmeprom_outstr(&ca[0], &ca[1]);
}
