/*	$NetBSD$ */

/*
 * Copyright (c) 2002
 *	Ichiro FUKUHARA <ichiro@ichiro.org>.
 * All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY ICHIRO FUKUHARA ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ICHIRO FUKUHARA OR THE VOICES IN HIS HEAD BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

/*
 * Slow peripheral bus of ixp12x0 Processor
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/device.h>

#include <machine/autoconf.h>
#include <sys/bus.h>

#include <arm/ixp12x0/ixp12x0var.h>
#include <arm/ixp12x0/ixpsipvar.h>

#include "locators.h"

static int	ixpsip_match(device_t, cfdata_t, void *);
static void	ixpsip_attach(device_t, device_t, void *);
static int	ixpsip_search(device_t, cfdata_t, const int *, void *);
static int	ixpsip_print(void *, const char *);

CFATTACH_DECL_NEW(ixpsip, sizeof(struct ixpsip_softc),
    ixpsip_match, ixpsip_attach, NULL, NULL);

int
ixpsip_match(device_t parent, cfdata_t cf, void *aux)
{
	return (1);
}

void
ixpsip_attach(device_t parent, device_t self, void *aux)
{
	struct ixpsip_softc *sc = device_private(self);
	sc->sc_iot = &ixp12x0_bs_tag;

	printf("\n");

	/*
	 *  Attach each devices
	 */
	config_search_ia(ixpsip_search, self, "ixpsip", NULL);
}

int
ixpsip_search(device_t parent, cfdata_t cf, const int *ldesc, void *aux)
{
	struct ixpsip_softc *sc = device_private(parent);
	struct ixpsip_attach_args sa;

	sa.sa_iot = sc->sc_iot;
	sa.sa_addr = cf->cf_loc[IXPSIPCF_ADDR];
	sa.sa_size = cf->cf_loc[IXPSIPCF_SIZE];
	sa.sa_intr = cf->cf_loc[IXPSIPCF_INTR];

	if (config_match(parent, cf, &sa) > 0)
		config_attach(parent, cf, &sa, ixpsip_print);

	return (0);
}

static int
ixpsip_print(void *aux, const char *name)
{
        struct ixpsip_attach_args *sa = aux;

	if (sa->sa_size)
		aprint_normal(" addr 0x%lx", sa->sa_addr);
	if (sa->sa_size > 1)
		aprint_normal("-0x%lx", sa->sa_addr + sa->sa_size - 1);
	if (sa->sa_intr > 1)
		aprint_normal(" intr %d", sa->sa_intr);

	return (UNCONF);
}
