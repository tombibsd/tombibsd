/* $NetBSD$ */

/*
 * Written by Matthias Drochner <drochner@NetBSD.org>.
 * Public domain.
 */

#include "../src/namespace.h"
#include <complex.h>
#include <math.h>

float
cabsf(float complex z)
{

	return hypotf(__real__ z, __imag__ z);
}
