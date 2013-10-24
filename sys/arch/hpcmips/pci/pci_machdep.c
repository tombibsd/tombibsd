#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

#include "opt_pci.h"

#include <sys/param.h>
#include <sys/systm.h>

#include <dev/pci/pcireg.h>
#include <dev/pci/pcivar.h>

int
pci_bus_devorder(pci_chipset_tag_t pc, int bus, uint8_t *devs, int maxdevs)
{
	return (*pc->pc_bus_devorder)(pc, bus, devs, maxdevs);
}
