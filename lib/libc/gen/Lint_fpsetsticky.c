/* $NetBSD$ */

/*
 * This file placed in the public domain.
 * Chris Demetriou, November 5, 1997.
 */

#include <ieeefp.h>

/*ARGSUSED*/
fp_except
fpsetsticky(s)
	fp_except s;
{
	fp_except rv = { 0 };

	return (rv);
}
