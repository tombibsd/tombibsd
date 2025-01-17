/*	$NetBSD$	*/

/*	$OpenBSD: limits.h,v 1.2 2000/07/31 20:06:02 millert Exp $	*/

/* 
 * Copyright (c) 1992-1994, The University of Utah and
 * the Computer Systems Laboratory at the University of Utah (CSL).
 * All rights reserved.
 *
 * Permission to use, copy, modify and distribute this software is hereby
 * granted provided that (1) source code retains these copyright, permission,
 * and disclaimer notices, and (2) redistributions including binaries
 * reproduce the notices in supporting documentation, and (3) all advertising
 * materials mentioning features or use of this software display the following
 * acknowledgement: ``This product includes software developed by the
 * Computer Systems Laboratory at the University of Utah.''
 *
 * THE UNIVERSITY OF UTAH AND CSL ALLOW FREE USE OF THIS SOFTWARE IN ITS "AS
 * IS" CONDITION.  THE UNIVERSITY OF UTAH AND CSL DISCLAIM ANY LIABILITY OF
 * ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * CSL requests users of this software to return to csl-dist@cs.utah.edu any
 * improvements that they make and grant CSL redistribution rights.
 *
 * 	Utah $Hdr: limits.h 1.6 94/12/16$
 */

/*
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)limits.h	8.3 (Berkeley) 1/4/94
 */

#ifndef	_MACHINE_LIMITS_H_
#define	_MACHINE_LIMITS_H_

#include <sys/featuretest.h>

#define	CHAR_BIT	8		/* number of bits in a char */

/*
 * According to ANSI (section 2.2.4.2), the values below must be usable by
 * #if preprocessing directives.  Additionally, the expression must have the
 * same type as would an expression that is an object of the corresponding
 * type converted according to the integral promotions.  The subtraction for
 * INT_MIN and LONG_MIN is so the value is not unsigned; 2147483648 is an
 * unsigned int for 32-bit two's complement ANSI compilers (section 3.1.3.2).
 * These numbers work for pcc as well.  The UINT_MAX and ULONG_MAX values
 * are written as hex so that GCC will be quiet about large integer constants.
 */
#define	UCHAR_MAX	0xff		/* max value for an unsigned char */
#define	SCHAR_MAX	0x7f		/* max value for a signed char */
#define	SCHAR_MIN	(-0x7f-1)	/* min value for a signed char */

#define	USHRT_MAX	0xffff		/* max value for an unsigned short */
#define	SHRT_MAX	0x7fff		/* max value for a short */
#define	SHRT_MIN	(-0x7fff-1)	/* min value for a short */

#define	UINT_MAX	0xffffffffU	/* max value for an unsigned int */
#define	INT_MAX		0x7fffffff	/* max value for an int */
#define	INT_MIN		(-0x7fffffff-1)	/* min value for an int */

#define	ULONG_MAX	0xffffffffUL	/* max value for an unsigned long */
#define	LONG_MAX	0x7fffffffL	/* max value for a long */
#define	LONG_MIN	(-0x7fffffffL-1)	/* min value for a long */

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_NETBSD_SOURCE)
#define	SSIZE_MAX	INT_MAX		/* max value for a ssize_t */

#if defined(_ISOC99_SOURCE) || (__STDC_VERSION__ - 0) >= 199901L || \
    defined(_NETBSD_SOURCE)
#define ULLONG_MAX      0xffffffffffffffffULL   /* max unsigned long long */
#define LLONG_MAX       0x7fffffffffffffffLL    /* max signed long long */
#define LLONG_MIN       (-0x7fffffffffffffffLL-1) /* min signed long long */
#endif

#if defined(_NETBSD_SOURCE)
#define	SSIZE_MIN	INT_MIN		/* min value for a ssize_t */
#define SIZE_T_MAX      UINT_MAX        /* max value for a size_t */

#define UQUAD_MAX       0xffffffffffffffffULL           /* max unsigned quad */
#define QUAD_MAX        0x7fffffffffffffffLL            /* max signed quad */
#define QUAD_MIN        (-0x7fffffffffffffffLL-1)       /* min signed quad */

#endif /* _NETBSD_SOURCE */
#endif /* _POSIX_C_SOURCE || _XOPEN_SOURCE || _NETBSD_SOURCE */

#if defined(_XOPEN_SOURCE) || defined(_NETBSD_SOURCE)
#define LONG_BIT	32
#define WORD_BIT	32

#ifndef DBL_DIG
#ifdef __DBL_DIG__
#define DBL_DIG         __DBL_DIG__
#else
#define DBL_DIG		15
#endif
#endif

#ifndef DBL_MAX
#ifdef __DBL_MAX__
#define DBL_MAX		__DBL_MAX__
#else
#define DBL_MAX		1.7976931348623157E+308
#endif
#endif

#ifndef DBL_MIN
#ifdef __DBL_MIN__
#define DBL_MIN		__DBL_MIN__
#else
#define DBL_MIN		2.2250738585072014E-308
#endif
#endif

#ifndef FLT_DIG
#ifdef __FLT_DIG__
#define FLT_DIG         __FLT_DIG__
#else
#define FLT_DIG         6
#endif
#endif

#ifndef FLT_MAX
#ifdef __FLT_MAX__
#define FLT_MAX		__FLT_MAX__
#else
#define FLT_MAX		3.40282347E+38F 
#endif
#endif

#ifndef FLT_MIN
#ifdef __FLT_MIN__
#define FLT_MIN		__FLT_MIN__
#else
#define FLT_MIN		1.17549435E-38F 
#endif
#endif

#endif

#endif /* _MACHINE_LIMITS_H_ */
