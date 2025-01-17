/*	$NetBSD$	*/

/*-
 * Copyright (c) 2001, 2002, 2004 The NetBSD Foundation, Inc.
 * All rights reserved.
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

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

#include "debug_kloader.h"

#include <sys/param.h>
#include <sys/systm.h>

#include <mips/cache.h>
#include <machine/kloader.h>

kloader_jumpfunc_t kloader_playstation2_jump;
kloader_bootfunc_t kloader_playstation2_boot;
void kloader_playstation2_reset(void);

struct kloader_ops kloader_playstation2_ops = {
	.jump = kloader_playstation2_jump,
	.boot = kloader_playstation2_boot,
	.reset = kloader_playstation2_reset,
};

void
kloader_reboot_setup(const char *filename)
{

	__kloader_reboot_setup(&kloader_playstation2_ops, filename);
}

void
kloader_playstation2_jump(kloader_bootfunc_t func, vaddr_t sp,
    struct kloader_bootinfo *info, struct kloader_page_tag *tag)
{

	mips_icache_sync_all();

	(*func)(info, tag);	/* 2nd-bootloader don't use stack */
	/* NOTREACHED */
}

void
kloader_playstation2_reset()
{

	((void (*)(void))0xbfc00000)();
	/* NOTREACHED */
}
