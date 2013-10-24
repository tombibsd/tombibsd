/* $NetBSD$ */

/*
 * Written by Matthias Drochner <drochner@NetBSD.org>.
 * Public domain.
 */

#include "../src/namespace.h"
#include <complex.h>
#include <math.h>

double
carg(double complex z)
{

	return atan2(__imag__ z, __real__ z);
}
