/*	$NetBSD$ */
/*	$OpenBSD: alipm.c,v 1.13 2007/05/03 12:19:01 dlg Exp $	*/

/*
 * Copyright (c) 2005 Mark Kettenis
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

#include <sys/param.h>
#include <sys/device.h>
#include <sys/kernel.h>
#include <sys/mutex.h>
#include <sys/proc.h>
#include <sys/systm.h>

#include <dev/i2c/i2cvar.h>

#include <dev/pci/pcidevs.h>
#include <dev/pci/pcireg.h>
#include <dev/pci/pcivar.h>

/*
 * Acer Labs M7101 Power register definitions.
 */

/* PCI configuration registers. */
#define ALIPM_CONF	0xd0		/* general configuration */
#define ALIPM_CONF_SMBEN	0x0400		/* enable SMBus */
#define ALIPM_BASE	0xe0		/* ACPI and SMBus base address */
#define ALIPM_SMB_HOSTC	0xf0		/* host configuration */
#define ALIPM_SMB_HOSTC_HSTEN	0x00000001	/* enable host controller */
#define ALIPM_SMB_HOSTC_CLOCK	0x00e00000	/* clock speed */
#define ALIPM_SMB_HOSTC_149K	0x00000000	/* 149 KHz clock */
#define ALIPM_SMB_HOSTC_74K	0x00200000	/*  74 KHz clock */
#define ALIPM_SMB_HOSTC_37K	0x00400000	/*  37 KHz clock */
#define ALIPM_SMB_HOSTC_223K	0x00800000	/* 223 KHz clock */
#define ALIPM_SMB_HOSTC_111K	0x00a00000	/* 111 KHz clock */
#define ALIPM_SMB_HOSTC_55K	0x00c00000	/*  55 KHz clock */

#define ALIPM_SMB_SIZE		32	/* SMBus I/O space size */

/* SMBus I/O registers */
#define ALIPM_SMB_HS	0x00		/* host status */
#define ALIPM_SMB_HS_IDLE	0x04
#define ALIPM_SMB_HS_BUSY	0x08	/* running a command */
#define ALIPM_SMB_HS_DONE	0x10	/* command completed */
#define ALIPM_SMB_HS_DEVERR	0x20	/* command error */
#define ALIPM_SMB_HS_BUSERR	0x40	/* transaction collision */
#define ALIPM_SMB_HS_FAILED	0x80	/* failed bus transaction */
#define ALIPM_SMB_HS_BITS \
  "\020\003IDLE\004BUSY\005DONE\006DEVERR\007BUSERR\010FAILED"
#define ALIPM_SMB_HC	0x01		/* host control */
#define ALIPM_SMB_HC_KILL	0x04		/* kill command */
#define ALIPM_SMB_HC_RESET	0x08		/* reset bus */
#define ALIPM_SMB_HC_CMD_QUICK	0x00		/* QUICK command */
#define ALIPM_SMB_HC_CMD_BYTE	0x10		/* BYTE command */
#define ALIPM_SMB_HC_CMD_BDATA	0x20		/* BYTE DATA command */
#define ALIPM_SMB_HC_CMD_WDATA	0x30		/* WORD DATA command */
#define ALIPM_SMB_HC_CMD_BLOCK 0x40		/* BLOCK command */
#define ALIPM_SMB_START		0x02	/* start command */
#define ALIPM_SMB_TXSLVA	0x03	/* transmit slave address */
#define ALIPM_SMB_TXSLVA_READ	(1 << 0)	/* read direction */
#define ALIPM_SMB_TXSLVA_ADDR(x) (((x) & 0x7f) << 1) /* 7-bit address */
#define ALIPM_SMB_HD0		0x04	/* host data 0 */
#define ALIPM_SMB_HD1		0x05	/* host data 1 */
#define ALIPM_SMB_HBDB		0x06	/* host block data byte */
#define ALIPM_SMB_HCMD		0x07	/* host command */

/*
 * Newer chips have a more standard, but different PCI configuration
 * register layout.
 */

#define ALIPM_SMB_BASE	0x14		/* SMBus base address */
#define ALIPM_SMB_HOSTX	0xe0		/* host configuration */

#ifdef ALIPM_DEBUG
#define DPRINTF(x) printf x
#else
#define DPRINTF(x)
#endif

#define ALIPM_DELAY	100
#define ALIPM_TIMEOUT	1

struct alipm_softc {
	device_t sc_dev;

	bus_space_tag_t sc_iot;
	bus_space_handle_t sc_ioh;

	struct i2c_controller sc_smb_tag;
	kmutex_t sc_smb_mutex;
};

static int	alipm_match(device_t, cfdata_t, void *);
static void	alipm_attach(device_t, device_t, void *);

int	alipm_smb_acquire_bus(void *, int);
void	alipm_smb_release_bus(void *, int);
int	alipm_smb_exec(void *, i2c_op_t, i2c_addr_t, const void *,
	    size_t, void *, size_t, int);

CFATTACH_DECL_NEW(alipm, sizeof(struct alipm_softc),
	alipm_match, alipm_attach, NULL, NULL);

static int
alipm_match(device_t parent, cfdata_t match, void *aux)
{
	struct pci_attach_args *pa = aux;

	if (PCI_VENDOR(pa->pa_id) == PCI_VENDOR_ALI &&
	    (PCI_PRODUCT(pa->pa_id) == PCI_PRODUCT_ALI_M7101))
		return (1);
	return (0);
}

static void
alipm_attach(device_t parent, device_t self, void *aux)
{
	struct alipm_softc *sc = device_private(self);
	struct pci_attach_args *pa = aux;
	struct i2cbus_attach_args iba;
	pcireg_t iobase, reg;
	bus_size_t iosize = ALIPM_SMB_SIZE;

	sc->sc_dev = self;

	/* Old chips don't have the PCI 2.2 Capabilities List. */
	reg = pci_conf_read(pa->pa_pc, pa->pa_tag, PCI_COMMAND_STATUS_REG);
	if ((reg & PCI_STATUS_CAPLIST_SUPPORT) == 0) {
		/* Map I/O space */
		iobase = pci_conf_read(pa->pa_pc, pa->pa_tag, ALIPM_BASE);
		sc->sc_iot = pa->pa_iot;
		if (iobase == 0 ||
		    bus_space_map(sc->sc_iot, iobase >> 16,
		    iosize, 0, &sc->sc_ioh)) {
			aprint_error_dev(sc->sc_dev, "can't map I/O space\n");
			return;
		}

		reg = pci_conf_read(pa->pa_pc, pa->pa_tag, ALIPM_CONF);
		if ((reg & ALIPM_CONF_SMBEN) == 0) {
			aprint_error_dev(sc->sc_dev, "SMBus disabled\n");
			goto fail;
		}

		reg = pci_conf_read(pa->pa_pc, pa->pa_tag, ALIPM_SMB_HOSTC);
		if ((reg & ALIPM_SMB_HOSTC_HSTEN) == 0) {
			aprint_error_dev(sc->sc_dev, "SMBus host disabled\n");
			goto fail;
		}
	} else {
		/* Map I/O space */
		if (pci_mapreg_map(pa, ALIPM_SMB_BASE, PCI_MAPREG_TYPE_IO, 0,
		    &sc->sc_iot, &sc->sc_ioh, NULL, &iosize)) {
			aprint_error_dev(sc->sc_dev, "can't map I/O space\n");
			return;
		}

		reg = pci_conf_read(pa->pa_pc, pa->pa_tag, ALIPM_SMB_HOSTX);
		if ((reg & ALIPM_SMB_HOSTC_HSTEN) == 0) {
			aprint_error_dev(sc->sc_dev, "SMBus host disabled\n");
			goto fail;
		}
	}

	switch (reg & ALIPM_SMB_HOSTC_CLOCK) {
	case ALIPM_SMB_HOSTC_149K:
		aprint_normal(": 149KHz clock\n");
		break;
	case ALIPM_SMB_HOSTC_74K:
		aprint_normal(": 74KHz clock\n");
		break;
	case ALIPM_SMB_HOSTC_37K:
		aprint_normal(": 37KHz clock\n");
		break;
	case ALIPM_SMB_HOSTC_223K:
		aprint_normal(": 223KHz clock\n");
		break;
	case ALIPM_SMB_HOSTC_111K:
		aprint_normal(": 111KHz clock\n");
		break;
	case ALIPM_SMB_HOSTC_55K:
		aprint_normal(": 55KHz clock\n");
		break;
	default:
		aprint_normal(" unknown clock speed\n");
		break;
	}
	aprint_naive("\n");

	/* Attach I2C bus */
	mutex_init(&sc->sc_smb_mutex, MUTEX_DEFAULT, IPL_NONE);
	sc->sc_smb_tag.ic_cookie = sc;
	sc->sc_smb_tag.ic_acquire_bus = alipm_smb_acquire_bus;
	sc->sc_smb_tag.ic_release_bus = alipm_smb_release_bus;
	sc->sc_smb_tag.ic_exec = alipm_smb_exec;

	memset(&iba, 0, sizeof iba);
	iba.iba_tag = &sc->sc_smb_tag;
	(void)config_found_ia(sc->sc_dev, "i2cbus", &iba, iicbus_print);

	return;

fail:
	bus_space_unmap(sc->sc_iot, sc->sc_ioh, iosize);
}

int
alipm_smb_acquire_bus(void *cookie, int flags)
{
	struct alipm_softc *sc = cookie;

	mutex_enter(&sc->sc_smb_mutex);
	return 0;
}

void
alipm_smb_release_bus(void *cookie, int flags)
{
	struct alipm_softc *sc = cookie;

	mutex_exit(&sc->sc_smb_mutex);
}

int
alipm_smb_exec(void *cookie, i2c_op_t op, i2c_addr_t addr,
    const void *cmdbuf, size_t cmdlen, void *buf, size_t len, int flags)
{
	struct alipm_softc *sc = cookie;
	u_int8_t *b;
	u_int8_t ctl, st;
	int retries, error = 0;

	DPRINTF(("%s: exec op %d, addr 0x%x, cmdlen %d, len %d, "
	    "flags 0x%x\n", device_xname(sc->sc_dev), op, addr, cmdlen,
	    len, flags));

	if (!I2C_OP_STOP_P(op) || cmdlen > 1 || len > 2 ||
	    (cmdlen == 0 && len > 1))
		return (EOPNOTSUPP);

	/* Clear status bits */
	bus_space_write_1(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_HS,
	    ALIPM_SMB_HS_DONE | ALIPM_SMB_HS_FAILED |
	    ALIPM_SMB_HS_BUSERR | ALIPM_SMB_HS_DEVERR);
	bus_space_barrier(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_HS, 1,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);

	/* Wait until bus is idle */
	for (retries = 1000; retries > 0; retries--) {
		st = bus_space_read_1(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_HS);
		bus_space_barrier(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_HS, 1,
		    BUS_SPACE_BARRIER_READ);
		if (st & (ALIPM_SMB_HS_IDLE | ALIPM_SMB_HS_FAILED |
		    ALIPM_SMB_HS_BUSERR | ALIPM_SMB_HS_DEVERR))
			break;
		DELAY(ALIPM_DELAY);
	}
	if (retries == 0) {
		aprint_error_dev(sc->sc_dev, "timeout st 0x%x\n", st);
		return (ETIMEDOUT);
	}
	if (st & (ALIPM_SMB_HS_FAILED |
	    ALIPM_SMB_HS_BUSERR | ALIPM_SMB_HS_DEVERR)) {
		aprint_error_dev(sc->sc_dev, "error st 0x%x\n", st);
		return (EIO);
	}

	/* Set slave address and transfer direction. */
	bus_space_write_1(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_TXSLVA,
	    ALIPM_SMB_TXSLVA_ADDR(addr) |
	    (I2C_OP_READ_P(op) ? ALIPM_SMB_TXSLVA_READ : 0));

	if (cmdlen > 0)
		/* Set command byte */
		bus_space_write_1(sc->sc_iot, sc->sc_ioh,
		     ALIPM_SMB_HCMD, ((const u_int8_t *)cmdbuf)[0]);

	if (I2C_OP_WRITE_P(op)) {
		/* Write data. */
		b = buf;
		if (cmdlen == 0 && len == 1)
			bus_space_write_1(sc->sc_iot, sc->sc_ioh,
			    ALIPM_SMB_HCMD, b[0]);
		else if (len > 0)
			bus_space_write_1(sc->sc_iot, sc->sc_ioh,
			    ALIPM_SMB_HD0, b[0]);
		if (len > 1)
			bus_space_write_1(sc->sc_iot, sc->sc_ioh,
			    ALIPM_SMB_HD1, b[1]);
	}

	/* Set SMBus command */
	if (cmdlen == 0) {
		if (len == 0)
			ctl = ALIPM_SMB_HC_CMD_QUICK;
		else
			ctl = ALIPM_SMB_HC_CMD_BYTE;
	} else if (len == 1)
		ctl = ALIPM_SMB_HC_CMD_BDATA;
	else
		ctl = ALIPM_SMB_HC_CMD_WDATA;
	bus_space_write_1(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_HC, ctl);

	/* Start transaction */
	bus_space_barrier(sc->sc_iot, sc->sc_ioh, 0, ALIPM_SMB_SIZE,
	    BUS_SPACE_BARRIER_WRITE);
	bus_space_write_1(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_START, 0xff);
	bus_space_barrier(sc->sc_iot, sc->sc_ioh, 0, ALIPM_SMB_SIZE,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);

	/* Poll for completion */
	DELAY(ALIPM_DELAY);
	for (retries = 1000; retries > 0; retries--) {
		st = bus_space_read_1(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_HS);
		bus_space_barrier(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_HS, 1,
		    BUS_SPACE_BARRIER_READ);
		if (st & (ALIPM_SMB_HS_IDLE | ALIPM_SMB_HS_FAILED |
		    ALIPM_SMB_HS_BUSERR | ALIPM_SMB_HS_DEVERR))
			break;
		DELAY(ALIPM_DELAY);
	}
	if (retries == 0) {
		aprint_error_dev(sc->sc_dev, "timeout st 0x%x, resetting\n",st);
		bus_space_write_1(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_HC,
		    ALIPM_SMB_HC_RESET);
		bus_space_barrier(sc->sc_iot, sc->sc_ioh, 0, ALIPM_SMB_SIZE,
		     BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
		st = bus_space_read_1(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_HS);
		bus_space_barrier(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_HS, 1,
		    BUS_SPACE_BARRIER_READ);
		error = ETIMEDOUT;
		goto done;
	}

	if ((st & ALIPM_SMB_HS_DONE) == 0) {
		bus_space_write_1(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_HC,
		     ALIPM_SMB_HC_KILL);
		bus_space_barrier(sc->sc_iot, sc->sc_ioh, 0, ALIPM_SMB_SIZE,
		     BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
		st = bus_space_read_1(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_HS);
		bus_space_barrier(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_HS, 1,
		    BUS_SPACE_BARRIER_READ);
		if ((st & ALIPM_SMB_HS_FAILED) == 0)
			aprint_error_dev(sc->sc_dev, "error st 0x%x\n", st);
	}

	/* Check for errors */
	if (st & (ALIPM_SMB_HS_FAILED |
	    ALIPM_SMB_HS_BUSERR | ALIPM_SMB_HS_DEVERR)) {
		error = EIO;
		goto done;
	}

	if (I2C_OP_READ_P(op)) {
		/* Read data */
		b = buf;
		if (len > 0) {
			b[0] = bus_space_read_1(sc->sc_iot, sc->sc_ioh,
			    ALIPM_SMB_HD0);
			bus_space_barrier(sc->sc_iot, sc->sc_ioh,
			    ALIPM_SMB_HD0, 1, BUS_SPACE_BARRIER_READ);
		}
		if (len > 1) {
			b[1] = bus_space_read_1(sc->sc_iot, sc->sc_ioh,
			    ALIPM_SMB_HD1);
			bus_space_barrier(sc->sc_iot, sc->sc_ioh,
			    ALIPM_SMB_HD1, 1, BUS_SPACE_BARRIER_READ);
		}
	}

done:
	/* Clear status bits */
	bus_space_write_1(sc->sc_iot, sc->sc_ioh, ALIPM_SMB_HS, st);

	return (error);
}
