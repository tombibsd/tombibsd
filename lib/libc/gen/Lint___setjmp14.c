/* $NetBSD$ */

/*
 * This file placed in the public domain.
 * Chris Demetriou, November 5, 1997.
 */

#include <setjmp.h>

/*ARGSUSED*/
int
__setjmp14(jmp_buf env)
{
	return 0;
}

/*ARGSUSED*/
void
__longjmp14(jmp_buf env, int val)
{
}
