/* $NetBSD$ */

/*
 * This file placed in the public domain.
 * Chris Demetriou, November 5, 1997.
 */

#include <ieeefp.h>

/*ARGSUSED*/
fp_rnd
fpsetround(r)
	fp_rnd r;
{
	fp_rnd rv = { 0 };

	return (rv);
}
