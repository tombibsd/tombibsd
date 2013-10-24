/* $NetBSD$ */

/*
 * This file placed in the public domain.
 * Chris Demetriou, November 5, 1997.
 */

#include <ieeefp.h>

/*ARGSUSED*/
fp_except
fpsetmask(m)
	fp_except m;
{
	fp_except rv = { 0 };

	return (rv);
}
