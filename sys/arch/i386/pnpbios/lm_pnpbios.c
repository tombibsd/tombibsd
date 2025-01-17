/*	$NetBSD$ */

/*-
 * Copyright (c) 2000 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Bill Squier.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/syslog.h>
#include <sys/device.h>
#include <sys/proc.h>

#include <sys/bus.h>

#include <dev/isa/isavar.h>
#include <dev/isa/isadmavar.h>

#include <i386/pnpbios/pnpbiosvar.h>

#include <dev/sysmon/sysmonvar.h>

#include <dev/ic/nslm7xvar.h>


int 	lm_pnpbios_match(device_t, cfdata_t, void *);
void 	lm_pnpbios_attach(device_t, device_t, void *);

int 	lm_pnpbios_hints_index(const char *);
uint8_t lm_pnpbios_readreg(struct lm_softc *, int);
void 	lm_pnpbios_writereg(struct lm_softc *, int, int);


CFATTACH_DECL_NEW(lm_pnpbios, sizeof(struct lm_softc),
    lm_pnpbios_match, lm_pnpbios_attach, NULL, NULL);

/*
 * XXX - no known pnpbios ids for lm series chips.
 */
struct lm_pnpbios_hint {
	char idstr[8];
	int io_region_idx_lm7x;
};

/*
 * Currently no known valid pnpbios id's - PNP0C02 is
 * for reserved motherboard resources, probing it is bad.
 */
struct lm_pnpbios_hint lm_pnpbios_hints[] = {
	{ { 0 }, 0 }
};


int
lm_pnpbios_hints_index(const char *idstr)
{
	int idx = 0;

	while (lm_pnpbios_hints[idx].idstr[0] != 0) {
		if (!strcmp(lm_pnpbios_hints[idx].idstr, idstr))
			return idx;
		++idx;
	}

	return -1;
}

int
lm_pnpbios_match(device_t parent, cfdata_t match, void *aux)
{
	struct pnpbiosdev_attach_args *aa = aux;
	struct lm_pnpbios_hint *wph;
	bus_space_tag_t iot;
	bus_space_handle_t ioh;
	int rv;

	int wphi;

	if ((wphi = lm_pnpbios_hints_index(aa->idstr)) == -1)
		return 0;

	wph = &lm_pnpbios_hints[wphi];

	if (pnpbios_io_map(aa->pbt, aa->resc, wph->io_region_idx_lm7x,
			   &iot, &ioh)) {
		return 0;
	}

	rv = lm_probe(iot, ioh);

	pnpbios_io_unmap(aa->pbt, aa->resc, wph->io_region_idx_lm7x,
			 iot, ioh);

	return rv;
}

void
lm_pnpbios_attach(device_t parent, device_t self, void *aux)
{
	struct lm_softc *sc = device_private(self);
	struct pnpbiosdev_attach_args *aa = aux;
	struct lm_pnpbios_hint *wph;

	wph = &lm_pnpbios_hints[lm_pnpbios_hints_index(aa->idstr)];

	if (pnpbios_io_map(aa->pbt, aa->resc, wph->io_region_idx_lm7x,
			   &sc->lm_iot, &sc->lm_ioh)) {
		aprint_error(": can't map i/o space\n");
		return;
	}

	aprint_naive("\n");
	aprint_normal("\n");
	pnpbios_print_devres(self, aa);

	/* Bus-independent attach */
	sc->lm_writereg = lm_pnpbios_writereg;
	sc->lm_readreg = lm_pnpbios_readreg;

	lm_attach(sc);
}

uint8_t
lm_pnpbios_readreg(struct lm_softc *sc, int reg)
{
	bus_space_write_1(sc->lm_iot, sc->lm_ioh, LMC_ADDR, reg);
	return (bus_space_read_1(sc->lm_iot, sc->lm_ioh, LMC_DATA));
}


void
lm_pnpbios_writereg(struct lm_softc *sc, int reg, int val)
{
	bus_space_write_1(sc->lm_iot, sc->lm_ioh, LMC_ADDR, reg);
	bus_space_write_1(sc->lm_iot, sc->lm_ioh, LMC_DATA, val);
}
