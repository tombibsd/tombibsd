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
/* __FBSDID("$FreeBSD: src/lib/libelf/libelf_xlate.c,v 1.3.2.1.2.1 2009/10/25 01:10:29 kensmith Exp $"); */

#include <assert.h>
#include <libelf.h>

#include "_libelf.h"

/*
 * Translate to/from the file representation of ELF objects.
 *
 * Translation could potentially involve the following
 * transformations:
 *
 * - an endianness conversion,
 * - a change of layout, as the file representation of ELF objects
 *   can differ from their in-memory representation.
 * - a change in representation due to a layout version change.
 */

Elf_Data *
_libelf_xlate(Elf_Data *dst, const Elf_Data *src, unsigned int encoding,
    int elfclass, int direction)
{
	size_t cnt, dsz, fsz, msz;
	uintptr_t sb, se, db, de;

	if (encoding == ELFDATANONE)
		encoding = _libelf_host_byteorder();

	if ((encoding != ELFDATA2LSB && encoding != ELFDATA2MSB) ||
	    dst == NULL || src == NULL || dst == src)	{
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	assert(elfclass == ELFCLASS32 || elfclass == ELFCLASS64);
	assert(direction == ELF_TOFILE || direction == ELF_TOMEMORY);

	if (dst->d_version != src->d_version) {
		LIBELF_SET_ERROR(UNIMPL, 0);
		return (NULL);
	}

	if  (src->d_buf == NULL || dst->d_buf == NULL) {
		LIBELF_SET_ERROR(DATA, 0);
		return (NULL);
	}

	if ((int) src->d_type < 0 || src->d_type >= ELF_T_NUM) {
		LIBELF_SET_ERROR(DATA, 0);
		return (NULL);
	}

	if ((fsz = (elfclass == ELFCLASS32 ? elf32_fsize : elf64_fsize)
	    (src->d_type, (size_t) 1, src->d_version)) == 0)
		return (NULL);

	msz = _libelf_msize(src->d_type, elfclass, src->d_version);

	assert(msz > 0);

	if (src->d_size % (direction == ELF_TOMEMORY ? fsz : msz)) {
		LIBELF_SET_ERROR(DATA, 0);
		return (NULL);
	}

	/*
	 * Determine the number of objects that need to be converted, and
	 * the space required for the converted objects in the destination
	 * buffer.
	 */
	if (direction == ELF_TOMEMORY) {
		cnt = src->d_size / fsz;
		dsz = cnt * msz;
	} else {
		cnt = src->d_size / msz;
		dsz = cnt * fsz;
	}

	if (dst->d_size  <  dsz) {
		LIBELF_SET_ERROR(DATA, 0);
		return (NULL);
	}

	sb = (uintptr_t) src->d_buf;
	se = sb + src->d_size;
	db = (uintptr_t) dst->d_buf;
	de = db + dst->d_size;

	/*
	 * Check for overlapping buffers.  Note that db == sb is
	 * allowed.
	 */
	if (db != sb && de > sb && se > db) {
		LIBELF_SET_ERROR(DATA, 0);
		return (NULL);
	}

	if ((direction == ELF_TOMEMORY ? db : sb) %
	    _libelf_malign(src->d_type, elfclass)) {
		LIBELF_SET_ERROR(DATA, 0);
		return (NULL);
	}

	dst->d_type = src->d_type;
	dst->d_size = dsz;

	if (src->d_size == 0 ||
	    (db == sb && encoding == _libelf_host_byteorder() && fsz == msz))
		return (dst);	/* nothing more to do */

	(_libelf_get_translator(src->d_type, direction, elfclass))(dst->d_buf,
	    src->d_buf, cnt, encoding != _libelf_host_byteorder());

	return (dst);
}
