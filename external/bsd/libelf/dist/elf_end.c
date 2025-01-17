/*	$NetBSD$	*/

/*-
 * Copyright (c) 2006 Joseph Koshy
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if HAVE_NBTOOL_CONFIG_H
# include "nbtool_config.h"
#endif

#include <sys/cdefs.h>
/* __FBSDID("$FreeBSD: src/lib/libelf/elf_end.c,v 1.1.10.1.2.1 2009/10/25 01:10:29 kensmith Exp $"); */

#include <sys/mman.h>

#include <assert.h>
#include <libelf.h>
#include <stdlib.h>

#include "_libelf.h"

int
elf_end(Elf *e)
{
	Elf *sv;
	Elf_Scn *scn, *tscn;

	if (e == NULL || e->e_activations == 0)
		return (0);

	if (--e->e_activations > 0)
		return (e->e_activations);

	assert(e->e_activations == 0);

	while (e && e->e_activations == 0) {
		switch (e->e_kind) {
		case ELF_K_AR:
			/*
			 * If we still have open child descriptors, we
			 * need to defer reclaiming resources till all
			 * the child descriptors for the archive are
			 * closed.
			 */
			if (e->e_u.e_ar.e_nchildren > 0)
				return (0);
			break;
		case ELF_K_ELF:
			/*
			 * Reclaim all section descriptors.
			 */
			STAILQ_FOREACH_SAFE(scn, &e->e_u.e_elf.e_scn, s_next, tscn)
 				scn = _libelf_release_scn(scn);
			break;
		case ELF_K_NUM:
			assert(0);
		default:
			break;
		}

		if (e->e_flags & LIBELF_F_MMAP)
			(void) munmap(e->e_rawfile, e->e_rawsize);
		if (e->e_flags & LIBELF_F_MALLOC)
			(void) free(e->e_rawfile);

		sv = e;
		if ((e = e->e_parent) != NULL)
			e->e_u.e_ar.e_nchildren--;
		sv = _libelf_release_elf(sv);
	}

	return (0);
}

