/*	$NetBSD$	*/

#if defined(_KERNEL) && !defined(_MODULE)

#define MACHINE			"ofppc"

#endif /* _KERNEL && !_MODULE */

/* at this offset we mmap() the PCI IO range in display drivers */
#define PCI_MAGIC_IO_RANGE      0xfeff0000

#include <powerpc/param.h>
