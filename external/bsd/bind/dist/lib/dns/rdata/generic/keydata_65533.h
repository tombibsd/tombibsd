/*	$NetBSD$	*/

/*
 * Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef GENERIC_KEYDATA_65533_H
#define GENERIC_KEYDATA_65533_H 1

/* Id: keydata_65533.h,v 1.2 2009/06/30 02:52:32 each Exp  */

typedef struct dns_rdata_keydata {
	dns_rdatacommon_t	common;
	isc_mem_t *		mctx;
	isc_uint32_t		refresh;      /* Timer for refreshing data */
	isc_uint32_t		addhd;	      /* Hold-down timer for adding */
	isc_uint32_t		removehd;     /* Hold-down timer for removing */
	isc_uint16_t		flags;	      /* Copy of DNSKEY_48 */
	isc_uint8_t		protocol;
	isc_uint8_t		algorithm;
	isc_uint16_t		datalen;
	unsigned char *		data;
} dns_rdata_keydata_t;

#endif /* GENERIC_KEYDATA_65533_H */
