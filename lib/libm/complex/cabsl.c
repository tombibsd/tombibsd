/* $NetBSD$ */

/*
 * Public domain.
 */

#include "../src/namespace.h"
#include <complex.h>
#include <math.h>

long double
cabsl(long double complex z)
{

	return hypotl(__real__ z, __imag__ z);
}
