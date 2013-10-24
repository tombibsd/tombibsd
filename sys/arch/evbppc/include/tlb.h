/*	$NetBSD$	*/

#ifdef _KERNEL_OPT
#include "opt_ppcarch.h"
#endif

#ifdef PPC_IBM4XX
#include <powerpc/ibm4xx/tlb.h>

#define	ppc4xx_tlbflags(va, pa)        (0)
#endif
