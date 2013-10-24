/*
 *	local definitions for libdos
 *
 *	written by ITOH Yasufumi
 *	public domain
 *
 *	$NetBSD$
 */

#include <machine/asm.h>

#ifdef __ELF__
#define CERROR		__DOS_CERROR
#define PRCERROR	__DOS_PRCERROR
#else
#define CERROR		DOS_CERROR
#define PRCERROR	DOS_PRCERROR
#endif
