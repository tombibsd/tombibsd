/*	$NetBSD$	*/

/*
 * Copyright (c) 1996 Christopher G. Demetriou.  All rights reserved.
 * Copyright (c) 1995 Charles M. Hannum.  All rights reserved.
 *
 * This code is derived from public-domain software written by
 * Roland McGrath.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by Charles M. Hannum.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/device.h>
#include <sys/termios.h>

#include <sys/bus.h>
#include <sys/intr.h>

#include <dev/ic/comreg.h>
#include <dev/ic/comvar.h>

#include <dev/isa/isavar.h>
#include <dev/isa/com_multi.h>

#define	NSLAVES	8

struct moxa_isa_softc {
	void *sc_ih;

	bus_space_tag_t sc_iot;
	int sc_iobase;

	int sc_alive;			/* mask of slave units attached */
	void *sc_slaves[NSLAVES];	/* com device unit numbers */
	bus_space_handle_t sc_slaveioh[NSLAVES];
};

int moxa_isaprobe(device_t, cfdata_t, void *);
void moxa_isaattach(device_t, device_t, void *);
int moxa_isaintr(void *);

CFATTACH_DECL_NEW(moxa_isa, sizeof(struct moxa_isa_softc),
    moxa_isaprobe, moxa_isaattach, NULL, NULL);

int
moxa_isaprobe(device_t parent, cfdata_t self, void *aux)
{
	struct isa_attach_args *ia = aux;
	bus_space_tag_t iot = ia->ia_iot;
	bus_space_handle_t ioh;
	int i, iobase, rv = 1;

	/*
	 * Do the normal com probe for the first UART and assume
	 * its presence, and the ability to map the other UARTS,
	 * means there is a multiport board there.
	 * XXX Needs more robustness.
	 */

	if (ia->ia_nio < 1)
		return (0);
	if (ia->ia_nirq < 1)
		return (0);

	if (ISA_DIRECT_CONFIG(ia))
		return (0);

	/* Disallow wildcarded i/o address. */
	if (ia->ia_io[0].ir_addr == ISA_UNKNOWN_PORT)
		return (0);
	if (ia->ia_irq[0].ir_irq == ISA_UNKNOWN_IRQ)
		return (0);

	/* if the first port is in use as console, then it. */
	if (com_is_console(iot, ia->ia_io[0].ir_addr, 0))
		goto checkmappings;

	if (bus_space_map(iot, ia->ia_io[0].ir_addr, COM_NPORTS, 0, &ioh)) {
		rv = 0;
		goto out;
	}
	rv = comprobe1(iot, ioh);
	bus_space_unmap(iot, ioh, COM_NPORTS);
	if (rv == 0)
		goto out;

checkmappings:
	for (i = 1, iobase = ia->ia_io[0].ir_addr; i < NSLAVES; i++) {
		iobase += COM_NPORTS;

		if (com_is_console(iot, iobase, 0))
			continue;

		if (bus_space_map(iot, iobase, COM_NPORTS, 0, &ioh)) {
			rv = 0;
			goto out;
		}
		bus_space_unmap(iot, ioh, COM_NPORTS);
	}

out:
	if (rv) {
		ia->ia_nio = 1;
		ia->ia_io[0].ir_size = NSLAVES * COM_NPORTS;

		ia->ia_nirq = 1;

		ia->ia_niomem = 0;
		ia->ia_ndrq = 0;
	}
	return (rv);
}

void
moxa_isaattach(device_t parent, device_t self, void *aux)
{
	struct moxa_isa_softc *sc = device_private(self);
	struct isa_attach_args *ia = aux;
	struct commulti_attach_args ca;
	bus_space_tag_t iot = ia->ia_iot;
	int i, iobase;

	printf("\n");

	sc->sc_iot = ia->ia_iot;
	sc->sc_iobase = ia->ia_io[0].ir_addr;

	for (i = 0; i < NSLAVES; i++) {
		iobase = sc->sc_iobase + i * COM_NPORTS;
		if (!com_is_console(iot, iobase, &sc->sc_slaveioh[i]) &&
		    bus_space_map(iot, iobase, COM_NPORTS, 0,
			&sc->sc_slaveioh[i])) {
			aprint_error_dev(self, "can't map i/o space for slave %d\n", i);
			return;
		}
	}

	for (i = 0; i < NSLAVES; i++) {
		ca.ca_slave = i;
		ca.ca_iot = sc->sc_iot;
		ca.ca_ioh = sc->sc_slaveioh[i];
		ca.ca_iobase = sc->sc_iobase + i * COM_NPORTS;
		ca.ca_noien = 1;

		sc->sc_slaves[i] = config_found(self, &ca, commultiprint);
		if (sc->sc_slaves[i] != NULL)
			sc->sc_alive |= 1 << i;
	}

	sc->sc_ih = isa_intr_establish(ia->ia_ic, ia->ia_irq[0].ir_irq,
	    IST_EDGE, IPL_SERIAL, moxa_isaintr, sc);
}

int
moxa_isaintr(void *arg)
{
	struct moxa_isa_softc *sc = arg;
	int bits;
	int rv = 0;

	bits = sc->sc_alive;
	if (bits == 0)
		return (0);

	for (;;rv = 0) {
#define	TRY(n) \
		if (bits & (1 << (n))) \
			rv += comintr(sc->sc_slaves[n]);
		TRY(0);
		TRY(1);
		TRY(2);
		TRY(3);
		TRY(4);
		TRY(5);
		TRY(6);
		TRY(7);
#undef TRY
		if (rv == 0)
			return (1);
 	}
}
