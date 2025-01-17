/* $NetBSD$ */

/*-
 * Copyright (c)2008 Citrus Project,
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

#ifndef _CITRUS_LC_TEMPLATE_H_
#define _CITRUS_LC_TEMPLATE_H_

static __inline int
_PREFIX(create_impl)(const char * __restrict root,
    const char * __restrict name, _CATEGORY_TYPE ** __restrict pdata)
{
	char path[PATH_MAX + 1];
	int ret;
	struct _region file;
	struct _citrus_db *db;
	struct _memstream ms;
	_CATEGORY_TYPE *data;

	snprintf(path, sizeof(path),
	    "%s/%s/" _CATEGORY_DB, root, name);
	ret = _map_file(&file, path);
	if (ret) {
		ret = ENOENT;
	} else {
		data = malloc(sizeof(*data));
		if (!data) {
			ret = ENOMEM;
		} else {
			ret = _db_open(&db, &file, _CATEGORY_MAGIC,
			    &_db_hash_std, NULL);
			if (!ret) {
				ret = _PREFIX(init_normal)(data, db);
				_db_close(db);
			} else {
				_memstream_bind(&ms, &file);
				ret = _PREFIX(init_fallback)(data, &ms);
			}
			if (!ret)
				*pdata = data;
			else
				free(data);
		}
		_unmap_file(&file);
	}
	return ret;
}

#include "nb_lc_template.h"

#endif /* _CITRUS_LC_TEMPLATE_H_ */
