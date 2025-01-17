/*	$NetBSD$	*/

/*
 * Copyright 1996 The Board of Trustees of The Leland Stanford
 * Junior University. All Rights Reserved.
 *
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appear in all copies.  Stanford University
 * makes no representations about the suitability of this
 * software for any purpose.  It is provided "as is" without
 * express or implied warranty.
 *
 * This driver was contributed by Jonathan Stone.
 */

/*
 * LANCE on Decstation kn01/kn220(?) baseboard.
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

#include "opt_inet.h"

#include <sys/param.h>
#include <sys/socket.h>
#include <sys/systm.h>
#include <sys/device.h>

#include <net/if.h>
#include <net/if_ether.h>
#include <net/if_media.h>

#ifdef INET
#include <netinet/in.h>
#include <netinet/if_inarp.h>
#endif

#include <dev/ic/lancevar.h>
#include <dev/ic/am7990var.h>

#include <dev/tc/if_levar.h>
#include <pmax/ibus/ibusvar.h>
#include <pmax/pmax/kn01.h>

static void le_dec_copyfrombuf_gap2(struct lance_softc *, void *, int, int);
static void le_dec_copytobuf_gap2(struct lance_softc *, void *, int, int);
static void le_dec_zerobuf_gap2(struct lance_softc *, int, int);


static int le_pmax_match(device_t, cfdata_t, void *);
static void le_pmax_attach(device_t, device_t, void *);

CFATTACH_DECL_NEW(le_pmax, sizeof(struct le_softc),
    le_pmax_match, le_pmax_attach, NULL, NULL);

int
le_pmax_match(device_t parent, cfdata_t cf, void *aux)
{
	struct ibus_attach_args *d = aux;

	if (strcmp("lance", d->ia_name) != 0)
		return (0);
	return (1);
}

void
le_pmax_attach(device_t parent, device_t self, void *aux)
{
	struct le_softc *lesc = device_private(self);
	struct lance_softc *sc = &lesc->sc_am7990.lsc;
	uint8_t *cp;
	struct ibus_attach_args *ia = aux;

	/*
	 * It's on the baseboard, with a dedicated interrupt line.
	 */
	sc->sc_dev = self;
	lesc->sc_r1 = (struct lereg1 *)(ia->ia_addr);
	sc->sc_mem = (void *)MIPS_PHYS_TO_KSEG1(KN01_SYS_LANCE_B_START);
	cp = (uint8_t *)(MIPS_PHYS_TO_KSEG1(KN01_SYS_CLOCK) + 1);

	sc->sc_copytodesc = le_dec_copytobuf_gap2;
	sc->sc_copyfromdesc = le_dec_copyfrombuf_gap2;
	sc->sc_copytobuf = le_dec_copytobuf_gap2;
	sc->sc_copyfrombuf = le_dec_copyfrombuf_gap2;
	sc->sc_zerobuf = le_dec_zerobuf_gap2;

	dec_le_common_attach(&lesc->sc_am7990, cp);

	ibus_intr_establish(parent, (void *)ia->ia_cookie, IPL_NET,
	    am7990_intr, sc);
}

/*
 * gap2: two bytes of data followed by two bytes of pad.
 *
 * Buffers must be 4-byte aligned.  The code doesn't worry about
 * doing an extra byte.
 */

void
le_dec_copytobuf_gap2(struct lance_softc *sc, void *fromv, int boff, int len)
{
	volatile uint8_t *buf = sc->sc_mem;
	uint8_t *from = fromv;
	volatile uint16_t *bptr;

	if (boff & 0x1) {
		/* handle unaligned first byte */
		bptr = ((volatile uint16_t *)buf) + (boff - 1);
		*bptr = (*from++ << 8) | (*bptr & 0xff);
		bptr += 2;
		len--;
	} else
		bptr = ((volatile uint16_t *)buf) + boff;
	while (len > 1) {
		*bptr = (from[1] << 8) | (from[0] & 0xff);
		bptr += 2;
		from += 2;
		len -= 2;
	}
	if (len == 1)
		*bptr = (uint16_t)*from;
}

void
le_dec_copyfrombuf_gap2(struct lance_softc *sc, void *tov, int boff, int len)
{
	volatile void *buf = sc->sc_mem;
	uint8_t *to = tov;
	volatile uint16_t *bptr;
	uint16_t tmp;

	if (boff & 0x1) {
		/* handle unaligned first byte */
		bptr = ((volatile uint16_t *)buf) + (boff - 1);
		*to++ = (*bptr >> 8) & 0xff;
		bptr += 2;
		len--;
	} else
		bptr = ((volatile uint16_t *)buf) + boff;
	while (len > 1) {
		tmp = *bptr;
		*to++ = tmp & 0xff;
		*to++ = (tmp >> 8) & 0xff;
		bptr += 2;
		len -= 2;
	}
	if (len == 1)
		*to = *bptr & 0xff;
}

static void
le_dec_zerobuf_gap2(struct lance_softc *sc, int boff, int len)
{
	volatile void *buf = sc->sc_mem;
	volatile uint16_t *bptr;

	if ((unsigned int)boff & 0x1) {
		bptr = ((volatile uint16_t *)buf) + (boff - 1);
		*bptr &= 0xff;
		bptr += 2;
		len--;
	} else
		bptr = ((volatile uint16_t *)buf) + boff;
	while (len > 0) {
		*bptr = 0;
		bptr += 2;
		len -= 2;
	}
}
