/*	$NetBSD$	*/

/*	$OpenBSD: fpbits.h,v 1.4 2001/03/29 03:58:18 mickey Exp $	*/

/*
 * Copyright 1996 1995 by Open Software Foundation, Inc.
 *              All Rights Reserved
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appears in all copies and
 * that both the copyright notice and this permission notice appear in
 * supporting documentation.
 *
 * OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
 * NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*
 * pmk1.1
 */
/*
 * (c) Copyright 1986 HEWLETT-PACKARD COMPANY
 *
 * To anyone who acknowledges that this file is provided "AS IS"
 * without any express or implied warranty:
 *     permission to use, copy, modify, and distribute this file
 * for any purpose is hereby granted without fee, provided that
 * the above copyright notice and this notice appears in all
 * copies, and that the name of Hewlett-Packard Company not be
 * used in advertising or publicity pertaining to distribution
 * of the software without specific, written prior permission.
 * Hewlett-Packard Company makes no representations about the
 * suitability of this software for any purpose.
 */

/*
 *  These macros are designed to be portable to all machines that have
 *  a wordsize greater than or equal to 32 bits that support the portable
 *  C compiler and the standard C preprocessor.  Wordsize (default 32)
 *  and bitfield assignment (default left-to-right,  unlike VAX, PDP-11)
 *  should be predefined using the constants HOSTWDSZ and BITFRL and
 *  the C compiler "-D" flag (e.g., -DHOSTWDSZ=36 -DBITFLR for the DEC-20).
 *  Note that the macro arguments assume that the integer being referenced
 *  is a 32-bit integer (right-justified on the 20) and that bit 0 is the
 *  most significant bit.
 */

#ifndef HOSTWDSZ
#define	HOSTWDSZ	32
#endif


/*###########################  Macros  ######################################*/

/*-------------------------------------------------------------------------
 * NewDeclareBitField_Reference - Declare a structure similar to the simulator
 * function "DeclBitfR" except its use is restricted to occur within a larger
 * enclosing structure or union definition.  This declaration is an unnamed
 * structure with the argument, name, as the member name and the argument,
 * uname, as the element name.
 *----------------------------------------------------------------------- */
#define Bitfield_extract(start, length, object)		\
    ((object) >> (HOSTWDSZ - (start) - (length)) &	\
    ((unsigned)-1 >> (HOSTWDSZ - (length))))

#define Bitfield_signed_extract(start, length, object) \
    ((int)((object) << start) >> (HOSTWDSZ - (length)))

#define Bitfield_mask(start, len, object)		\
    ((object) & (((unsigned)-1 >> (HOSTWDSZ-len)) << (HOSTWDSZ-start-len)))

#define Bitfield_deposit(value,start,len,object)  object = \
    ((object) & ~(((unsigned)-1 >> (HOSTWDSZ-(len))) << (HOSTWDSZ-(start)-(len)))) | \
    (((value) & ((unsigned)-1 >> (HOSTWDSZ-(len)))) << (HOSTWDSZ-(start)-(len)))

