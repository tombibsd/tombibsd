/*	$NetBSD$	*/

/*-
 * Copyright (c) 2000, 2001 The NetBSD Foundation, Inc.
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

#ifndef _ACORN32_LOCK_H_
#define _ACORN32_LOCK_H_

#include <sys/param.h>

#ifdef _KERNEL_OPT
#include "opt_multiprocessor.h"
#endif

#if defined(_HARDKERNEL) && defined(MULTIPROCESSOR)

#include <arm/cpufunc.h>

static __inline int
__swp(int __val, volatile unsigned char *__ptr)
{

	__asm volatile("swpb %0, %1, [%2]"
	    : "=r" (__val) : "r" (__val), "r" (__ptr) : "memory");
	return __val;
}

static __inline void __attribute__((__unused__))
__cpu_simple_lock_init(__cpu_simple_lock_t *alp)
{

	*alp = __SIMPLELOCK_UNLOCKED;
}

static __inline void __attribute__((__unused__))
__cpu_simple_lock(__cpu_simple_lock_t *alp)
{

	while (__swp(__SIMPLELOCK_LOCKED, alp) != __SIMPLELOCK_UNLOCKED)
		continue;
	cpu_idcache_wbinv_all();
}

static __inline int __attribute__((__unused__))
__cpu_simple_lock_try(__cpu_simple_lock_t *alp)
{
	int __result;

	__result = __swp(__SIMPLELOCK_LOCKED, alp) == __SIMPLELOCK_UNLOCKED;
	if (__result)
		cpu_idcache_wbinv_all();
	return __result;
}

static __inline void __attribute__((__unused__))
__cpu_simple_unlock(__cpu_simple_lock_t *alp)
{

	*alp = __SIMPLELOCK_UNLOCKED;
}

#else /* !(_HARDKERNEL && MULTIPROCESSOR) */
#include <arm/lock.h>
#endif /* !(_HARDKERNEL && MULTIPROCESSOR) */
#endif
