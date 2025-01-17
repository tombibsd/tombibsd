/*	$NetBSD$	*/

/*-
 * Copyright (c)2003 Citrus Project,
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

#ifndef _CITRUS_CTYPE_FALLBACK_H_
#define _CITRUS_CTYPE_FALLBACK_H_

/* fallback functions for 0x00000002 */
int _citrus_ctype_btowc_fallback(_citrus_ctype_rec_t * __restrict,
				 int, wint_t * __restrict);
int _citrus_ctype_wctob_fallback(_citrus_ctype_rec_t * __restrict,
				 wint_t, int * __restrict);

/* fallback functions for 0x00000003 */
int _citrus_ctype_mbsnrtowcs_fallback(_citrus_ctype_rec_t * __restrict,
				      wchar_t * __restrict,
				      const char ** __restrict, size_t,
				      size_t, void * __restrict,
				      size_t * __restrict);
int _citrus_ctype_wcsnrtombs_fallback(_citrus_ctype_rec_t * __restrict,
				     char * __restrict,
				     const wchar_t ** __restrict, size_t,
				     size_t, void * __restrict,
				     size_t * __restrict);

#endif
