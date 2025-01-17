/* $NetBSD$ */

#ifndef _CATS_ISA_MACHDEP_H_
#define _CATS_ISA_MACHDEP_H_
#include <arm/isa_machdep.h>

#ifdef _KERNEL
#define ISA_FOOTBRIDGE_IRQ IRQ_IN_L2
void	isa_footbridge_init(u_int, u_int);
#endif /* _KERNEL */

#endif /* _CATS_ISA_MACHDEP_H_ */
