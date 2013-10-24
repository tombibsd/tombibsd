/*	$NetBSD$	*/

#include <arm/pci_machdep.h>
#define __HAVE_PCI_CONF_HOOK
int pci_conf_hook(void *, int, int, int, pcireg_t);

