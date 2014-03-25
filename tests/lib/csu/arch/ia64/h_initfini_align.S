/*	$NetBSD$	*/

#include <machine/asm.h>

RCSID("$NetBSD$")

ENTRY(check_stack_alignment, 0)
	.prologue
	.regstk 0, 2, 0, 0

	alloc loc0 = ar.pfs, 0, 2, 0, 0

	.body
	mov ret0 = 1
	;;
	
	/* ar.bsp has an 8-byte alignment requirement */
 	mov loc1 = ar.bsp
	;;
	
	and loc1 = 7, loc1
	;;
	
	cmp.eq	p1, p0 = 0, loc1
	(p0)	mov ret0 = 0
	;;
	
	/* sp has a 16-byte alignment requirement */
	(p1)	mov loc1 = sp
	;;
	(p1)	and loc1 = 15, loc1
	;;
	
	(p1)	cmp.eq p1, p0 = 0, loc1
	(p0)	mov ret0 = 0

	br.ret.sptk.few rp
