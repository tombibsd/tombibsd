/* $NetBSD$ */

/*
 * Public domain.
 */

#include "../src/namespace.h"
#include <complex.h>
#include <math.h>

long double
cargl(long double complex z)
{

	return atan2l(__imag__ z, __real__ z);
}
