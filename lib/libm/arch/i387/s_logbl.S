/*
 * Written by J.T. Conklin <jtc@NetBSD.org>.
 * Public domain.
 */

#include <machine/asm.h>

#include "abi.h"

RCSID("$NetBSD$")

ENTRY(logbl)
	fldt	ARG_LONG_DOUBLE_ONE
	fxtract
	fstp	%st
	ret
