/*	$NetBSD$	*/


#include <sys/types.h>
#include <machine/mon.h>

#include "libsa.h"
#include "net.h"

int hz = 1000;

satime_t 
getsecs(void)
{
	long ticks;

	ticks = getticks();
	return ((ticks / hz));
}

long 
getticks(void)
{
	long ticks;

	ticks = *romVectorPtr->nmiClock;
	return (ticks);
}
