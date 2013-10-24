/*	$NetBSD$	*/

#include <m68k/asm.h>

	.text

ASENTRY_NOPROFILE(start)
	jra	_C_LABEL(bootxxx)
