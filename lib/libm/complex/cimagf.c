/* $NetBSD$ */

/*
 * Written by Matthias Drochner <drochner@NetBSD.org>.
 * Public domain.
 */

#include <complex.h>
#include "../src/math_private.h"

float
cimagf(float complex z)
{
	float_complex w = { .z = z };

	return (IMAG_PART(w));
}
