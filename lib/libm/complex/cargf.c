/* $NetBSD$ */

/*
 * Written by Matthias Drochner <drochner@NetBSD.org>.
 * Public domain.
 */

#include "../src/namespace.h"
#include <complex.h>
#include <math.h>

float
cargf(float complex z)
{

	return atan2f(__imag__ z, __real__ z);
}
