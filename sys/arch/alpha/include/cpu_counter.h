/* $NetBSD$ */

/*-
 * Copyright (c) 2000 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Jason R. Thorpe.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _ALPHA_CPU_COUNTER_H_
#define _ALPHA_CPU_COUNTER_H_

/*
 * Machine-specific support for CPU counter.
 */

#ifdef _KERNEL

#include <machine/cpu.h>
#include <machine/rpb.h>

#define cc_calibrate_mp(ci)	\
	alpha_multicast_ipi(cpus_running, ALPHA_IPI_MICROSET)

/* Process Cycle Counter is always available. */
#define cpu_hascounter()	(1)
#define cpu_counter()		cpu_counter32()

static __inline uint32_t
cpu_counter32(void)
{

	/*
	 * Only the lower 32 bits of the PCC are an actual cycle
	 * counter.  Thankfully, the rnd(4) code only wants a
	 * 32-bit value anyway.
	 */
	return (alpha_rpcc() & 0xffffffffU);
}

static __inline uint64_t
cpu_frequency(struct cpu_info *ci)
{

	return (ci->ci_pcc_freq);
}

#endif /* _KERNEL */

#endif /* !_ALPHA_CPU_COUNTER_H_ */
