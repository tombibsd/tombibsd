/*	$NetBSD$	*/

#include <machine/asm.h>
#include "bootxx.h"

	.text

GLOBAL(block_size)
	.long	512

GLOBAL(block_count)
	.long	MAXBLOCKNUM

GLOBAL(block_table)
	.space	(MAXBLOCKNUM * 4)
