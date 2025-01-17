/*	$NetBSD$ */
/*-
 * Copyright (c) 1992, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1992, 1993, 1994, 1995, 1996
 *	Keith Bostic.  All rights reserved.
 *
 * See the LICENSE file for redistribution information.
 */

#include "config.h"

#include <sys/cdefs.h>
#if 0
#ifndef lint
static const char sccsid[] = "Id: v_increment.c,v 10.16 2001/06/25 15:19:31 skimo Exp  (Berkeley) Date: 2001/06/25 15:19:31 ";
#endif /* not lint */
#else
__RCSID("$NetBSD$");
#endif

#include <sys/types.h>
#include <sys/queue.h>
#include <sys/time.h>

#include <bitstring.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/common.h"
#include "vi.h"

static const CHAR_T *fmt[] = {
#define	DEC	0
	L("%ld"),
#define	SDEC	1
	L("%+ld"),
#define	HEXC	2
	L("0X%0*lX"),
#define	HEXL	3
	L("0x%0*lx"),
#define	OCTAL	4
	L("%#0*lo"),
};

static void inc_err __P((SCR *, enum nresult));

/*
 * v_increment -- [count]#[#+-]
 *	Increment/decrement a keyword number.
 *
 * PUBLIC: int v_increment __P((SCR *, VICMD *));
 */
int
v_increment(SCR *sp, VICMD *vp)
{
	enum nresult nret;
	u_long ulval, change;
	long ltmp, lval;
	size_t beg, blen, end, len, nlen, wlen;
	int base, isempty, rval;
	CHAR_T *bp, *p, *t, nbuf[100]; 
	const CHAR_T *ntype;

	/* Validate the operator. */
	if (vp->character == L('#'))
		vp->character = L('+');
	if (vp->character != L('+') && vp->character != L('-')) {
		v_emsg(sp, vp->kp->usage, VIM_USAGE);
		return (1);
	}

	/* If new value set, save it off, but it has to fit in a long. */
	if (F_ISSET(vp, VC_C1SET)) {
		if (vp->count > LONG_MAX) {
			inc_err(sp, NUM_OVER);
			return (1);
		}
		change = vp->count;
	} else
		change = 1;

	/* Get the line. */
	if (db_eget(sp, vp->m_start.lno, &p, &len, &isempty)) {
		if (isempty)
			goto nonum;
		return (1);
	}

	/*
	 * Skip any leading space before the number.  Getting a cursor word
	 * implies moving the cursor to its beginning, if we moved, refresh
	 * now.
	 */
	for (beg = vp->m_start.cno; beg < len && ISSPACE((UCHAR_T)p[beg]); ++beg);
	if (beg >= len)
		goto nonum;
	if (beg != vp->m_start.cno) {
		sp->cno = beg;
		(void)vs_refresh(sp, 0);
	}

#undef	isoctal
#define	isoctal(c)	(ISDIGIT(c) && (c) != L('8') && (c) != L('9'))

	/*
	 * Look for 0[Xx], or leading + or - signs, guess at the base.
	 * The character after that must be a number.  Wlen is set to
	 * the remaining characters in the line that could be part of
	 * the number.
	 */
	wlen = len - beg;
	if (p[beg] == L('0') && wlen > 2 &&
	    (p[beg + 1] == L('X') || p[beg + 1] == L('x'))) {
		base = 16;
		end = beg + 2;
		if (!ISXDIGIT((UCHAR_T)p[end]))
			goto decimal;
		ntype = p[beg + 1] == L('X') ? fmt[HEXC] : fmt[HEXL];
	} else if (p[beg] == L('0') && wlen > 1) {
		base = 8;
		end = beg + 1;
		if (!isoctal((UCHAR_T)p[end]))
			goto decimal;
		ntype = fmt[OCTAL];
	} else if (wlen >= 1 && (p[beg] == L('+') || p[beg] == L('-'))) {
		base = 10;
		end = beg + 1;
		ntype = fmt[SDEC];
		if (!ISDIGIT((UCHAR_T)p[end]))
			goto nonum;
	} else {
decimal:	base = 10;
		end = beg;
		ntype = fmt[DEC];
		if (!ISDIGIT(p[end])) {
nonum:			msgq(sp, M_ERR, "181|Cursor not in a number");
			return (1);
		}
	}

	/* Find the end of the word, possibly correcting the base. */
	while (++end < len) {
		switch (base) {
		case 8:
			if (isoctal((UCHAR_T)p[end]))
				continue;
			if (p[end] == L('8') || p[end] == L('9')) {
				base = 10;
				ntype = fmt[DEC];
				continue;
			}
			break;
		case 10:
			if (ISDIGIT((UCHAR_T)p[end]))
				continue;
			break;
		case 16:
			if (ISXDIGIT((UCHAR_T)p[end]))
				continue;
			break;
		default:
			abort();
			/* NOTREACHED */
		}
		break;
	}
	wlen = (end - beg);

	/*
	 * XXX
	 * If the line was at the end of the buffer, we have to copy it
	 * so we can guarantee that it's NULL-terminated.  We make the
	 * buffer big enough to fit the line changes as well, and only
	 * allocate once.
	 */
	GET_SPACE_RETW(sp, bp, blen, len + 50);
	if (end == len) {
		MEMMOVEW(bp, &p[beg], wlen);
		bp[wlen] = L('\0');
		t = bp;
	} else
		t = &p[beg];

	/*
	 * Octal or hex deal in unsigned longs, everything else is done
	 * in signed longs.
	 */
	if (base == 10) {
		if ((nret = nget_slong(sp, &lval, t, NULL, 10)) != NUM_OK)
			goto err;
		ltmp = vp->character == L('-') ? -change : change;
		if (lval > 0 && ltmp > 0 &&
		    !NPFITS(LONG_MAX, (unsigned long)lval, (unsigned long)ltmp)) {
			nret = NUM_OVER;
			goto err;
		}
		if (lval < 0 && ltmp < 0 && !NNFITS(LONG_MIN, lval, ltmp)) {
			nret = NUM_UNDER;
			goto err;
		}
		lval += ltmp;
		/* If we cross 0, signed numbers lose their sign. */
		if (lval == 0 && ntype == fmt[SDEC])
			ntype = fmt[DEC];
		nlen = SPRINTF(nbuf, SIZE(nbuf), ntype, lval);
	} else {
		if ((nret = nget_uslong(sp, &ulval, t, NULL, base)) != NUM_OK)
			goto err;
		if (vp->character == L('+')) {
			if (!NPFITS(ULONG_MAX, ulval, change)) {
				nret = NUM_OVER;
				goto err;
			}
			ulval += change;
		} else {
			if (ulval < change) {
				nret = NUM_UNDER;
				goto err;
			}
			ulval -= change;
		}

		/* Correct for literal "0[Xx]" in format. */
		if (base == 16)
			wlen -= 2;

		nlen = SPRINTF(nbuf, SIZE(nbuf), ntype, wlen, ulval);
	}

	/* Build the new line. */
	MEMMOVEW(bp, p, beg);
	MEMMOVEW(bp + beg, nbuf, nlen);
	MEMMOVEW(bp + beg + nlen, p + end, len - beg - (end - beg));
	len = beg + nlen + (len - beg - (end - beg));

	nret = NUM_OK;
	rval = db_set(sp, vp->m_start.lno, bp, len);

	if (0) {
err:		rval = 1;
		inc_err(sp, nret);
	}
	if (bp != NULL)
		FREE_SPACEW(sp, bp, blen);
	return (rval);
}

static void
inc_err(SCR *sp, enum nresult nret)
{
	switch (nret) {
	case NUM_ERR:
		break;
	case NUM_OK:
		abort();
		/* NOREACHED */
	case NUM_OVER:
		msgq(sp, M_ERR, "182|Resulting number too large");
		break;
	case NUM_UNDER:
		msgq(sp, M_ERR, "183|Resulting number too small");
		break;
	}
}
