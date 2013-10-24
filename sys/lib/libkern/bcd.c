/* $NetBSD$ */

/*
 * Convert a single byte between (unsigned) packed bcd and binary.
 * Public domain.
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0,"$NetBSD$");

#include <lib/libkern/libkern.h>

unsigned int
bcdtobin(unsigned int bcd)
{

        return (((bcd >> 4) & 0x0f) * 10 + (bcd & 0x0f));
}

unsigned int
bintobcd(unsigned int bin)
{

	return ((((bin / 10) << 4) & 0xf0) | (bin % 10));
}
