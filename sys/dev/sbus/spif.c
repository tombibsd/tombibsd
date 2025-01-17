/*	$NetBSD$	*/
/*	$OpenBSD: spif.c,v 1.12 2003/10/03 16:44:51 miod Exp $	*/

/*
 * Copyright (c) 1999-2002 Jason L. Wright (jason@thought.net)
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Effort sponsored in part by the Defense Advanced Research Projects
 * Agency (DARPA) and Air Force Research Laboratory, Air Force
 * Materiel Command, USAF, under agreement number F30602-01-2-0537.
 *
 */

/*
 * Driver for the SUNW,spif: 8 serial, 1 parallel sbus board
 * based heavily on Iain Hibbert's driver for the MAGMA cards
 */

/* Ported to NetBSD 2.0 by Hauke Fath */


#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

#include "spif.h"
#if NSPIF > 0

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/device.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/malloc.h>
#include <sys/tty.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/syslog.h>
#include <sys/conf.h>
#include <sys/errno.h>
#include <sys/kauth.h>
#include <sys/intr.h>

#include <sys/bus.h>
#include <machine/autoconf.h>
#include <machine/promlib.h>

#include <dev/sbus/sbusvar.h>

#include <dev/sbus/spifvar.h>
#include <dev/sbus/spifreg.h>

#include "ioconf.h"

/* Autoconfig stuff */

CFATTACH_DECL_NEW(spif, sizeof(struct spif_softc),
    spif_match, spif_attach, NULL, NULL);

CFATTACH_DECL_NEW(stty, sizeof(struct stty_softc),
    stty_match, stty_attach, NULL, NULL);

CFATTACH_DECL_NEW(sbpp, sizeof(struct sbpp_softc),
    sbpp_match, sbpp_attach, NULL, NULL);

dev_type_open(stty_open);
dev_type_close(stty_close);
dev_type_read(stty_read);
dev_type_write(stty_write);
dev_type_ioctl(stty_ioctl);
dev_type_stop(stty_stop);
dev_type_tty(stty_tty);
dev_type_poll(stty_poll);

const struct cdevsw stty_cdevsw = {
	.d_open = stty_open,
	.d_close = stty_close,
	.d_read = stty_read,
	.d_write = stty_write,
	.d_ioctl = stty_ioctl,
	.d_stop = stty_stop,
	.d_tty = stty_tty,
	.d_poll = stty_poll,
	.d_mmap = nommap,
	.d_kqfilter = ttykqfilter,
	.d_discard = nodiscard,
	.d_flag = D_TTY
};

dev_type_open(sbpp_open);
dev_type_close(sbpp_close);
dev_type_read(sbpp_read);
dev_type_write(sbpp_write);
dev_type_ioctl(sbpp_ioctl);
dev_type_poll(sbpp_poll);

const struct cdevsw sbpp_cdevsw = {
	.d_open = sbpp_open,
	.d_close = sbpp_close,
	.d_read = sbpp_read,
	.d_write = sbpp_write,
	.d_ioctl = sbpp_ioctl,
	.d_stop = nostop,
	.d_tty = notty,
	.d_poll = sbpp_poll,
	.d_mmap = nommap,
	.d_kqfilter = nokqfilter,
	.d_discard = nodiscard,
	.d_flag = D_OTHER
};


/* normal STC access */
#define	STC_WRITE(sc,r,v)	\
    bus_space_write_1((sc)->sc_bustag, (sc)->sc_stch, (r), (v))
#define	STC_READ(sc,r)		\
    bus_space_read_1((sc)->sc_bustag, (sc)->sc_stch, (r))

/* IACK STC access */
#define	ISTC_WRITE(sc,r,v)	\
    bus_space_write_1((sc)->sc_bustag, (sc)->sc_istch, (r), (v))
#define	ISTC_READ(sc,r)		\
    bus_space_read_1((sc)->sc_bustag, (sc)->sc_istch, (r))

/* PPC access */
#define	PPC_WRITE(sc,r,v)	\
    bus_space_write_1((sc)->sc_bustag, (sc)->sc_ppch, (r), (v))
#define	PPC_READ(sc,r)		\
    bus_space_read_1((sc)->sc_bustag, (sc)->sc_ppch, (r))

#define	DTR_WRITE(sc,port,v)						\
    do {								\
	sc->sc_ttys->sc_port[(port)].sp_dtr = v;			\
	bus_space_write_1((sc)->sc_bustag,				\
	    sc->sc_dtrh, port, (v == 0) ? 1 : 0);			\
    } while (0)

#define	DTR_READ(sc,port)	((sc)->sc_ttys->sc_port[(port)].sp_dtr)


int
spif_match(device_t parent, cfdata_t vcf, void *aux)
{
	struct sbus_attach_args *sa = aux;

	if (strcmp(vcf->cf_name, sa->sa_name) &&
	    strcmp("SUNW,spif", sa->sa_name))
		return (0);
	return (1);
}

void
spif_attach(device_t parent, device_t self, void *aux)
{
	struct spif_softc *sc = device_private(self);
	struct sbus_attach_args *sa = aux;

	sc->sc_dev = self;

	if (sa->sa_nintr != 2) {
		printf(": expected %d interrupts, got %d\n", 2, sa->sa_nintr);
		return;
	}

	if (sa->sa_nreg != 1) {
		printf(": expected %d registers, got %d\n", 1, sa->sa_nreg);
		return;
	}

	sc->sc_bustag = sa->sa_bustag;
	if (sbus_bus_map(sa->sa_bustag, sa->sa_slot,
	    sa->sa_offset, sa->sa_size,
	    0, &sc->sc_regh) != 0) {
		printf(": can't map registers\n");
		return;
	}

	if (bus_space_subregion(sc->sc_bustag, sc->sc_regh,
	    DTR_REG_OFFSET, DTR_REG_LEN, &sc->sc_dtrh) != 0) {
		printf(": can't map dtr regs\n");
		goto fail_unmapregs;
	}

	if (bus_space_subregion(sc->sc_bustag, sc->sc_regh,
	    STC_REG_OFFSET, STC_REG_LEN, &sc->sc_stch) != 0) {
		printf(": can't map dtr regs\n");
		goto fail_unmapregs;
	}

	if (bus_space_subregion(sc->sc_bustag, sc->sc_regh,
	    ISTC_REG_OFFSET, ISTC_REG_LEN, &sc->sc_istch) != 0) {
		printf(": can't map dtr regs\n");
		goto fail_unmapregs;
	}

	if (bus_space_subregion(sc->sc_bustag, sc->sc_regh,
	    PPC_REG_OFFSET, PPC_REG_LEN, &sc->sc_ppch) != 0) {
		printf(": can't map dtr regs\n");
		goto fail_unmapregs;
	}

	sc->sc_ppcih = bus_intr_establish(sa->sa_bustag,
	    sa->sa_intr[PARALLEL_INTR].oi_pri, IPL_SERIAL, spif_ppcintr, sc);
	if (sc->sc_ppcih == NULL) {
		printf(": failed to establish ppc interrupt\n");
		goto fail_unmapregs;
	}

	sc->sc_stcih = bus_intr_establish(sa->sa_bustag,
	    sa->sa_intr[SERIAL_INTR].oi_pri, IPL_SERIAL, spif_stcintr, sc);
	if (sc->sc_stcih == NULL) {
		printf(": failed to establish stc interrupt\n");
		goto fail_unmapregs;
	}

	sc->sc_softih = softint_establish(SOFTINT_SERIAL, spif_softintr, sc);
	if (sc->sc_softih == NULL) {
		printf(": can't get soft intr\n");
		goto fail_unmapregs;
	}

	sc->sc_node = sa->sa_node;

	sc->sc_rev = prom_getpropint(sc->sc_node, "revlev", 0);

	sc->sc_osc = prom_getpropint(sc->sc_node, "verosc", 0);
	switch (sc->sc_osc) {
	case SPIF_OSC10:
		sc->sc_osc = 10000000;
		break;
	case SPIF_OSC9:
	default:
		sc->sc_osc = 9830400;
		break;
	}

	sc->sc_nser = 8;
	sc->sc_npar = 1;

	sc->sc_rev2 = STC_READ(sc, STC_GFRCR);
	STC_WRITE(sc, STC_GSVR, 0);

	stty_write_ccr(sc, CD180_CCR_CMD_RESET | CD180_CCR_RESETALL);
	while (STC_READ(sc, STC_GSVR) != 0xff);
	while (STC_READ(sc, STC_GFRCR) != sc->sc_rev2);

	STC_WRITE(sc, STC_PPRH, CD180_PPRH);
	STC_WRITE(sc, STC_PPRL, CD180_PPRL);
	STC_WRITE(sc, STC_MSMR, SPIF_MSMR);
	STC_WRITE(sc, STC_TSMR, SPIF_TSMR);
	STC_WRITE(sc, STC_RSMR, SPIF_RSMR);
	STC_WRITE(sc, STC_GSVR, 0);
	STC_WRITE(sc, STC_GSCR1, 0);
	STC_WRITE(sc, STC_GSCR2, 0);
	STC_WRITE(sc, STC_GSCR3, 0);

	printf(": rev %x chiprev %x osc %sMHz\n",
	    sc->sc_rev, sc->sc_rev2, clockfreq(sc->sc_osc));

	(void)config_found(self, stty_match, NULL);
	(void)config_found(self, sbpp_match, NULL);

	return;

fail_unmapregs:
	bus_space_unmap(sa->sa_bustag, sc->sc_regh, sa->sa_size);
}

int
stty_match(device_t parent, cfdata_t vcf, void *aux)
{
	struct spif_softc *sc = device_private(parent);

	return (aux == stty_match && sc->sc_ttys == NULL);
}

void
stty_attach(device_t parent, device_t dev, void *aux)
{
	struct spif_softc *sc = device_private(parent);
	struct stty_softc *ssc = device_private(dev);
	int port;

	sc->sc_dev = dev;
	sc->sc_ttys = ssc;

	for (port = 0; port < sc->sc_nser; port++) {
		struct stty_port *sp = &ssc->sc_port[port];
		struct tty *tp;

		DTR_WRITE(sc, port, 0);

		tp = tty_alloc();

		tp->t_oproc = stty_start;
		tp->t_param = stty_param;

		sp->sp_tty = tp;
		sp->sp_sc = sc;
		sp->sp_channel = port;

		sp->sp_rbuf = malloc(STTY_RBUF_SIZE, M_DEVBUF, M_NOWAIT);
		if(sp->sp_rbuf == NULL)
			break;

		sp->sp_rend = sp->sp_rbuf + STTY_RBUF_SIZE;
	}

	ssc->sc_nports = port;

	printf(": %d tty%s\n", port, port == 1 ? "" : "s");
}

int
stty_open(dev_t dev, int flags, int mode, struct lwp *l)
{
	struct spif_softc *csc;
	struct stty_softc *sc;
	struct stty_port *sp;
	struct tty *tp;
	int card = SPIF_CARD(dev);
	int port = SPIF_PORT(dev);

	sc = device_lookup_private(&stty_cd, card);
	csc = device_lookup_private(&spif_cd, card);
	if (sc == NULL || csc == NULL)
		return (ENXIO);

	if (port >= sc->sc_nports)
		return (ENXIO);

	sp = &sc->sc_port[port];
	tp = sp->sp_tty;
	tp->t_dev = dev;

	if (kauth_authorize_device_tty(l->l_cred, KAUTH_DEVICE_TTY_OPEN, tp))
		return (EBUSY);

	mutex_spin_enter(&tty_lock);
	if (!ISSET(tp->t_state, TS_ISOPEN) && tp->t_wopen == 0) {
		ttychars(tp);
		tp->t_iflag = TTYDEF_IFLAG;
		tp->t_oflag = TTYDEF_OFLAG;
		tp->t_cflag = TTYDEF_CFLAG;
		if (ISSET(sp->sp_openflags, TIOCFLAG_CLOCAL))
			SET(tp->t_cflag, CLOCAL);
		if (ISSET(sp->sp_openflags, TIOCFLAG_CRTSCTS))
			SET(tp->t_cflag, CRTSCTS);
		if (ISSET(sp->sp_openflags, TIOCFLAG_MDMBUF))
			SET(tp->t_cflag, MDMBUF);
		tp->t_lflag = TTYDEF_LFLAG;
		tp->t_ispeed = tp->t_ospeed = TTYDEF_SPEED;

		sp->sp_rput = sp->sp_rget = sp->sp_rbuf;

		STC_WRITE(csc, STC_CAR, sp->sp_channel);
		stty_write_ccr(csc, CD180_CCR_CMD_RESET|CD180_CCR_RESETCHAN);
		STC_WRITE(csc, STC_CAR, sp->sp_channel);

		stty_param(tp, &tp->t_termios);

		ttsetwater(tp);

		STC_WRITE(csc, STC_SRER, CD180_SRER_CD | CD180_SRER_RXD);

		if (ISSET(sp->sp_openflags, TIOCFLAG_SOFTCAR) || sp->sp_carrier)
			SET(tp->t_state, TS_CARR_ON);
		else
			CLR(tp->t_state, TS_CARR_ON);
	}

	if (!ISSET(flags, O_NONBLOCK)) {
		while (!ISSET(tp->t_cflag, CLOCAL) &&
		    !ISSET(tp->t_state, TS_CARR_ON)) {
			int error;
			error = ttysleep(tp, &tp->t_rawcv, true, 0);
			if (error != 0) {
				mutex_spin_exit(&tty_lock);
				return (error);
			}
		}
	}
	mutex_spin_exit(&tty_lock);

	return ((*tp->t_linesw->l_open)(dev, tp));
}

int
stty_close(dev_t dev, int flags, int mode, struct lwp *l)
{
	struct stty_softc *sc = device_lookup_private(&stty_cd, SPIF_CARD(dev));
	struct stty_port *sp = &sc->sc_port[SPIF_PORT(dev)];
	struct spif_softc *csc = sp->sp_sc;
	struct tty *tp = sp->sp_tty;
	int port = SPIF_PORT(dev);
	int s;

	(*tp->t_linesw->l_close)(tp, flags);
	s = spltty();

	if (ISSET(tp->t_cflag, HUPCL) || !ISSET(tp->t_state, TS_ISOPEN)) {
		stty_modem_control(sp, 0, DMSET);
		STC_WRITE(csc, STC_CAR, port);
		STC_WRITE(csc, STC_CCR,
		    CD180_CCR_CMD_RESET|CD180_CCR_RESETCHAN);
	}

	splx(s);
	ttyclose(tp);
	return (0);
}

int
stty_ioctl(dev_t dev, u_long cmd, void *data, int flags, struct lwp *l)
{
	struct stty_softc *stc = device_lookup_private(&stty_cd,
						       SPIF_CARD(dev));
	struct stty_port *sp = &stc->sc_port[SPIF_PORT(dev)];
	struct spif_softc *sc = sp->sp_sc;
	struct tty *tp = sp->sp_tty;
	int error;

	error = (*tp->t_linesw->l_ioctl)(tp, cmd, data, flags, l);
	if (error >= 0)
		return (error);

	error = ttioctl(tp, cmd, data, flags, l);
	if (error >= 0)
		return (error);

	error = 0;

	switch (cmd) {
	case TIOCSBRK:
		SET(sp->sp_flags, STTYF_SET_BREAK);
		STC_WRITE(sc, STC_CAR, sp->sp_channel);
		STC_WRITE(sc, STC_SRER,
		    STC_READ(sc, STC_SRER) | CD180_SRER_TXD);
		break;
	case TIOCCBRK:
		SET(sp->sp_flags, STTYF_CLR_BREAK);
		STC_WRITE(sc, STC_CAR, sp->sp_channel);
		STC_WRITE(sc, STC_SRER,
		    STC_READ(sc, STC_SRER) | CD180_SRER_TXD);
		break;
	case TIOCSDTR:
		stty_modem_control(sp, TIOCM_DTR, DMBIS);
		break;
	case TIOCCDTR:
		stty_modem_control(sp, TIOCM_DTR, DMBIC);
		break;
	case TIOCMBIS:
		stty_modem_control(sp, *((int *)data), DMBIS);
		break;
	case TIOCMBIC:
		stty_modem_control(sp, *((int *)data), DMBIC);
		break;
	case TIOCMGET:
		*((int *)data) = stty_modem_control(sp, 0, DMGET);
		break;
	case TIOCMSET:
		stty_modem_control(sp, *((int *)data), DMSET);
		break;
	case TIOCGFLAGS:
		*((int *)data) = sp->sp_openflags;
		break;
	case TIOCSFLAGS:
		if (kauth_authorize_device_tty(l->l_cred,
		    KAUTH_DEVICE_TTY_PRIVSET, tp))
			error = EPERM;
		else
			sp->sp_openflags = *((int *)data) &
			    (TIOCFLAG_SOFTCAR | TIOCFLAG_CLOCAL |
			     TIOCFLAG_CRTSCTS | TIOCFLAG_MDMBUF);
		break;
	default:
		error = ENOTTY;
	}

	return (error);
}

int
stty_modem_control(struct stty_port *sp, int bits, int how)
{
	struct spif_softc *csc = sp->sp_sc;
	struct tty *tp = sp->sp_tty;
	int s, msvr;

	s = spltty();
	STC_WRITE(csc, STC_CAR, sp->sp_channel);

	switch (how) {
	case DMGET:
		bits = TIOCM_LE;
		if (DTR_READ(csc, sp->sp_channel))
			bits |= TIOCM_DTR;
		msvr = STC_READ(csc, STC_MSVR);
		if (ISSET(msvr, CD180_MSVR_DSR))
			bits |= TIOCM_DSR;
		if (ISSET(msvr, CD180_MSVR_CD))
			bits |= TIOCM_CD;
		if (ISSET(msvr, CD180_MSVR_CTS))
			bits |= TIOCM_CTS;
		if (ISSET(msvr, CD180_MSVR_RTS))
			bits |= TIOCM_RTS;
		break;
	case DMSET:
		DTR_WRITE(csc, sp->sp_channel, ISSET(bits, TIOCM_DTR) ? 1 : 0);
		if (ISSET(bits, TIOCM_RTS))
			STC_WRITE(csc, STC_MSVR,
			    STC_READ(csc, STC_MSVR) & (~CD180_MSVR_RTS));
		else
			STC_WRITE(csc, STC_MSVR,
			    STC_READ(csc, STC_MSVR) | CD180_MSVR_RTS);
		break;
	case DMBIS:
		if (ISSET(bits, TIOCM_DTR))
			DTR_WRITE(csc, sp->sp_channel, 1);
		if (ISSET(bits, TIOCM_RTS) && !ISSET(tp->t_cflag, CRTSCTS))
			STC_WRITE(csc, STC_MSVR,
			    STC_READ(csc, STC_MSVR) & (~CD180_MSVR_RTS));
		break;
	case DMBIC:
		if (ISSET(bits, TIOCM_DTR))
			DTR_WRITE(csc, sp->sp_channel, 0);
		if (ISSET(bits, TIOCM_RTS))
			STC_WRITE(csc, STC_MSVR,
			    STC_READ(csc, STC_MSVR) | CD180_MSVR_RTS);
		break;
	}

	splx(s);
	return (bits);
}

int
stty_param(struct tty *tp, struct termios *t)
{
	struct stty_softc *st = device_lookup_private(&stty_cd,
						      SPIF_CARD(tp->t_dev));
	struct stty_port *sp = &st->sc_port[SPIF_PORT(tp->t_dev)];
	struct spif_softc *sc = sp->sp_sc;
	uint8_t rbprl = 0, rbprh = 0, tbprl = 0, tbprh = 0;
	int s, opt;

	if (t->c_ospeed &&
	    stty_compute_baud(t->c_ospeed, sc->sc_osc, &tbprl, &tbprh))
		return (EINVAL);

	if (t->c_ispeed &&
	    stty_compute_baud(t->c_ispeed, sc->sc_osc, &rbprl, &rbprh))
		return (EINVAL);

	s = spltty();

	/* hang up line if ospeed is zero, otherwise raise DTR */
	stty_modem_control(sp, TIOCM_DTR,
	    (t->c_ospeed == 0 ? DMBIC : DMBIS));

	STC_WRITE(sc, STC_CAR, sp->sp_channel);

	opt = 0;
	if (ISSET(t->c_cflag, PARENB)) {
		opt |= CD180_COR1_PARMODE_NORMAL;
		opt |= (ISSET(t->c_cflag, PARODD) ?
				CD180_COR1_ODDPAR :
				CD180_COR1_EVENPAR);
	}
	else
		opt |= CD180_COR1_PARMODE_NO;

	if (!ISSET(t->c_iflag, INPCK))
		opt |= CD180_COR1_IGNPAR;

	if (ISSET(t->c_cflag, CSTOPB))
		opt |= CD180_COR1_STOP2;

	switch (t->c_cflag & CSIZE) {
	case CS5:
		opt |= CD180_COR1_CS5;
		break;
	case CS6:
		opt |= CD180_COR1_CS6;
		break;
	case CS7:
		opt |= CD180_COR1_CS7;
		break;
	default:
		opt |= CD180_COR1_CS8;
		break;
	}
	STC_WRITE(sc, STC_COR1, opt);
	stty_write_ccr(sc, CD180_CCR_CMD_COR|CD180_CCR_CORCHG1);

	opt = CD180_COR2_ETC;
	if (ISSET(t->c_cflag, CRTSCTS))
		opt |= CD180_COR2_CTSAE;
	STC_WRITE(sc, STC_COR2, opt);
	stty_write_ccr(sc, CD180_CCR_CMD_COR|CD180_CCR_CORCHG2);

	STC_WRITE(sc, STC_COR3, STTY_RX_FIFO_THRESHOLD);
	stty_write_ccr(sc, CD180_CCR_CMD_COR|CD180_CCR_CORCHG3);

	STC_WRITE(sc, STC_SCHR1, 0x11);
	STC_WRITE(sc, STC_SCHR2, 0x13);
	STC_WRITE(sc, STC_SCHR3, 0x11);
	STC_WRITE(sc, STC_SCHR4, 0x13);
	STC_WRITE(sc, STC_RTPR, 0x12);

	STC_WRITE(sc, STC_MCOR1, CD180_MCOR1_CDZD | STTY_RX_DTR_THRESHOLD);
	STC_WRITE(sc, STC_MCOR2, CD180_MCOR2_CDOD);
	STC_WRITE(sc, STC_MCR, 0);

	if (t->c_ospeed) {
		STC_WRITE(sc, STC_TBPRH, tbprh);
		STC_WRITE(sc, STC_TBPRL, tbprl);
	}

	if (t->c_ispeed) {
		STC_WRITE(sc, STC_RBPRH, rbprh);
		STC_WRITE(sc, STC_RBPRL, rbprl);
	}

	stty_write_ccr(sc, CD180_CCR_CMD_CHAN |
	    CD180_CCR_CHAN_TXEN | CD180_CCR_CHAN_RXEN);

	sp->sp_carrier = STC_READ(sc, STC_MSVR) & CD180_MSVR_CD;

	splx(s);
	return (0);
}

int
stty_read(dev_t dev, struct uio *uio, int flags)
{
	struct stty_softc *sc = device_lookup_private(&stty_cd, SPIF_CARD(dev));
	struct stty_port *sp = &sc->sc_port[SPIF_PORT(dev)];
	struct tty *tp = sp->sp_tty;

	return ((*tp->t_linesw->l_read)(tp, uio, flags));
}

int
stty_write(dev_t dev, struct uio *uio, int flags)
{
	struct stty_softc *sc = device_lookup_private(&stty_cd, SPIF_CARD(dev));
	struct stty_port *sp = &sc->sc_port[SPIF_PORT(dev)];
	struct tty *tp = sp->sp_tty;

	return ((*tp->t_linesw->l_write)(tp, uio, flags));
}

int
stty_poll(dev_t dev, int events, struct lwp *l)
{
	struct stty_softc *sc = device_lookup_private(&stty_cd, SPIF_CARD(dev));
	struct stty_port *sp = &sc->sc_port[SPIF_PORT(dev)];
	struct tty *tp = sp->sp_tty;

	return ((*tp->t_linesw->l_poll)(tp, events, l));
}

struct tty *
stty_tty(dev_t dev)
{
	struct stty_softc *sc = device_lookup_private(&stty_cd, SPIF_CARD(dev));
	struct stty_port *sp = &sc->sc_port[SPIF_PORT(dev)];

	return (sp->sp_tty);
}

void
stty_stop(struct tty *tp, int flags)
{
	struct stty_softc *sc = device_lookup_private(&stty_cd,
						      SPIF_CARD(tp->t_dev));
	struct stty_port *sp = &sc->sc_port[SPIF_PORT(tp->t_dev)];
	int s;

	s = spltty();
	if (ISSET(tp->t_state, TS_BUSY)) {
		if (!ISSET(tp->t_state, TS_TTSTOP))
			SET(tp->t_state, TS_FLUSH);
		SET(sp->sp_flags, STTYF_STOP);
	}
	splx(s);
}

void
stty_start(struct tty *tp)
{
	struct stty_softc *stc = device_lookup_private(&stty_cd,
						       SPIF_CARD(tp->t_dev));
	struct stty_port *sp = &stc->sc_port[SPIF_PORT(tp->t_dev)];
	struct spif_softc *sc = sp->sp_sc;
	int s;

	s = spltty();

	if (!ISSET(tp->t_state, TS_TTSTOP | TS_TIMEOUT | TS_BUSY)) {
		if (ttypull(tp)) {
			sp->sp_txc = ndqb(&tp->t_outq, 0);
			sp->sp_txp = tp->t_outq.c_cf;
			SET(tp->t_state, TS_BUSY);
			STC_WRITE(sc, STC_CAR, sp->sp_channel);
			STC_WRITE(sc, STC_SRER,
			    STC_READ(sc, STC_SRER) | CD180_SRER_TXD);
		}
	}

	splx(s);
}

int
spif_stcintr_rxexception(struct spif_softc *sc, int *needsoftp)
{
	struct stty_port *sp;
	uint8_t channel, *ptr;

	channel = CD180_GSCR_CHANNEL(STC_READ(sc, STC_GSCR1));
	sp = &sc->sc_ttys->sc_port[channel];
	ptr = sp->sp_rput;
	*ptr++ = STC_READ(sc, STC_RCSR);
	*ptr++ = STC_READ(sc, STC_RDR);
	if (ptr == sp->sp_rend)
		ptr = sp->sp_rbuf;
	if (ptr == sp->sp_rget) {
		if (ptr == sp->sp_rbuf)
			ptr = sp->sp_rend;
		ptr -= 2;
		SET(sp->sp_flags, STTYF_RING_OVERFLOW);
	}
	STC_WRITE(sc, STC_EOSRR, 0);
	*needsoftp = 1;
	sp->sp_rput = ptr;
	return (1);
}

int
spif_stcintr_rx(struct spif_softc *sc, int *needsoftp)
{
	struct stty_port *sp;
	uint8_t channel, *ptr, cnt;
	int i;

	channel = CD180_GSCR_CHANNEL(STC_READ(sc, STC_GSCR1));
	sp = &sc->sc_ttys->sc_port[channel];
	ptr = sp->sp_rput;
	cnt = STC_READ(sc, STC_RDCR);
	for (i = 0; i < cnt; i++) {
		*ptr++ = 0;
		(void)STC_READ(sc, STC_RCSR);
		*ptr++ = STC_READ(sc, STC_RDR);
		if (ptr == sp->sp_rend)
			ptr = sp->sp_rbuf;
		if (ptr == sp->sp_rget) {
			if (ptr == sp->sp_rbuf)
				ptr = sp->sp_rend;
			ptr -= 2;
			SET(sp->sp_flags, STTYF_RING_OVERFLOW);
			break;
		}
	}
	STC_WRITE(sc, STC_EOSRR, 0);
	if (cnt) {
		*needsoftp = 1;
		sp->sp_rput = ptr;
	}
	return (1);
}

int
spif_stcintr_tx(struct spif_softc *sc, int *needsoftp)
{
	struct stty_port *sp;
	uint8_t channel, ch;
	int cnt = 0;

	channel = CD180_GSCR_CHANNEL(STC_READ(sc, STC_GSCR1));
	sp = &sc->sc_ttys->sc_port[channel];
	if (!ISSET(sp->sp_flags, STTYF_STOP)) {
		if (ISSET(sp->sp_flags, STTYF_SET_BREAK)) {
			STC_WRITE(sc, STC_TDR, 0);
			STC_WRITE(sc, STC_TDR, 0x81);
			CLR(sp->sp_flags, STTYF_SET_BREAK);
			cnt += 2;
		}
		if (ISSET(sp->sp_flags, STTYF_CLR_BREAK)) {
			STC_WRITE(sc, STC_TDR, 0);
			STC_WRITE(sc, STC_TDR, 0x83);
			CLR(sp->sp_flags, STTYF_CLR_BREAK);
			cnt += 2;
		}

		while (sp->sp_txc > 0 && cnt < (CD180_TX_FIFO_SIZE-1)) {
			ch = *sp->sp_txp;
			sp->sp_txc--;
			sp->sp_txp++;

			if (ch == 0) {
				STC_WRITE(sc, STC_TDR, ch);
				cnt++;
			}
			STC_WRITE(sc, STC_TDR, ch);
			cnt++;
		}
	}

	if (sp->sp_txc == 0 ||
	    ISSET(sp->sp_flags, STTYF_STOP)) {
		STC_WRITE(sc, STC_SRER, STC_READ(sc, STC_SRER) &
		    (~CD180_SRER_TXD));
		CLR(sp->sp_flags, STTYF_STOP);
		SET(sp->sp_flags, STTYF_DONE);
		*needsoftp = 1;
	}

	STC_WRITE(sc, STC_EOSRR, 0);

	return (1);
}

int
spif_stcintr_mx(struct spif_softc *sc, int *needsoftp)
{
	struct stty_port *sp;
	uint8_t channel, mcr;

	channel = CD180_GSCR_CHANNEL(STC_READ(sc, STC_GSCR1));
	sp = &sc->sc_ttys->sc_port[channel];
	mcr = STC_READ(sc, STC_MCR);
	if (mcr & CD180_MCR_CD) {
		SET(sp->sp_flags, STTYF_CDCHG);
		*needsoftp = 1;
	}
	STC_WRITE(sc, STC_MCR, 0);
	STC_WRITE(sc, STC_EOSRR, 0);
	return (1);
}

int
spif_stcintr(void *vsc)
{
	struct spif_softc *sc = (struct spif_softc *)vsc;
	int needsoft = 0, r = 0, i;
	uint8_t ar;

	for (i = 0; i < 8; i++) {
		ar = ISTC_READ(sc, STC_RRAR) & CD180_GSVR_IMASK;
		if (ar == CD180_GSVR_RXGOOD)
			r |= spif_stcintr_rx(sc, &needsoft);
		else if (ar == CD180_GSVR_RXEXCEPTION)
			r |= spif_stcintr_rxexception(sc, &needsoft);
	}

	for (i = 0; i < 8; i++) {
		ar = ISTC_READ(sc, STC_TRAR) & CD180_GSVR_IMASK;
		if (ar == CD180_GSVR_TXDATA)
			r |= spif_stcintr_tx(sc, &needsoft);
	}

	for (i = 0; i < 8; i++) {
		ar = ISTC_READ(sc, STC_MRAR) & CD180_GSVR_IMASK;
		if (ar == CD180_GSVR_STATCHG)
			r |= spif_stcintr_mx(sc, &needsoft);
	}

	if (needsoft)
		softint_schedule(sc->sc_softih);
	return (r);
}

void
spif_softintr(void *vsc)
{
	struct spif_softc *sc = (struct spif_softc *)vsc;
	struct stty_softc *stc = sc->sc_ttys;
	int i, data, s, flags;
	uint8_t stat, msvr;
	struct stty_port *sp;
	struct tty *tp;

	if (stc != NULL) {
		for (i = 0; i < stc->sc_nports; i++) {
			sp = &stc->sc_port[i];
			tp = sp->sp_tty;

			if (!ISSET(tp->t_state, TS_ISOPEN))
				continue;

			while (sp->sp_rget != sp->sp_rput) {
				stat = sp->sp_rget[0];
				data = sp->sp_rget[1];
				sp->sp_rget += 2;
				if (sp->sp_rget == sp->sp_rend)
					sp->sp_rget = sp->sp_rbuf;

				if (stat & (CD180_RCSR_BE | CD180_RCSR_FE))
					data |= TTY_FE;

				if (stat & CD180_RCSR_PE)
					data |= TTY_PE;

				(*tp->t_linesw->l_rint)(data, tp);
			}

			s = splhigh();
			flags = sp->sp_flags;
			CLR(sp->sp_flags, STTYF_DONE | STTYF_CDCHG |
			    STTYF_RING_OVERFLOW);
			splx(s);

			if (ISSET(flags, STTYF_CDCHG)) {
				s = spltty();
				STC_WRITE(sc, STC_CAR, i);
				msvr = STC_READ(sc, STC_MSVR);
				splx(s);

				sp->sp_carrier = msvr & CD180_MSVR_CD;
				(*tp->t_linesw->l_modem)(tp,
				    sp->sp_carrier);
			}

			if (ISSET(flags, STTYF_RING_OVERFLOW)) {
				log(LOG_WARNING, "%s-%x: ring overflow\n",
					device_xname(stc->sc_dev), i);
			}

			if (ISSET(flags, STTYF_DONE)) {
				ndflush(&tp->t_outq,
				    sp->sp_txp - tp->t_outq.c_cf);
				CLR(tp->t_state, TS_BUSY);
				(*tp->t_linesw->l_start)(tp);
			}
		}
	}
}

void
stty_write_ccr(struct spif_softc *sc, uint8_t val)
{
	int tries = 100000;

	while (STC_READ(sc, STC_CCR) && tries--)
		/*EMPTY*/;
	if (tries == 0)
		aprint_error_dev(sc->sc_dev, "ccr timeout\n");
	STC_WRITE(sc, STC_CCR, val);
}

int
stty_compute_baud(speed_t speed, int clock, uint8_t *bprlp, uint8_t *bprhp)
{
	uint32_t rate;

	rate = (2 * clock) / (16 * speed);
	if (rate & 1)
		rate = (rate >> 1) + 1;
	else
		rate = rate >> 1;

	if (rate > 0xffff || rate == 0)
		return (1);

	*bprlp = rate & 0xff;
	*bprhp = (rate >> 8) & 0xff;
	return (0);
}

int
sbpp_match(device_t parent, cfdata_t vcf, void *aux)
{
	struct spif_softc *sc = device_private(parent);

	return (aux == sbpp_match && sc->sc_bpps == NULL);
}

void
sbpp_attach(device_t parent, device_t dev, void *aux)
{
	struct spif_softc *sc = device_private(parent);
	struct sbpp_softc *psc = device_private(dev);
	int port;

	sc->sc_bpps = psc;

	for (port = 0; port < sc->sc_npar; port++) {
	}

	psc->sc_nports = port;
	printf(": %d port%s\n", port, port == 1 ? "" : "s");
}

int
sbpp_open(dev_t dev, int flags, int mode, struct lwp *l)
{
	return (ENXIO);
}

int
sbpp_close(dev_t dev, int flags, int mode, struct lwp *l)
{
	return (ENXIO);
}

int
spif_ppcintr(void *v)
{
	return (0);
}

int
sbpp_read(dev_t dev, struct uio *uio, int flags)
{
	return (sbpp_rw(dev, uio));
}

int
sbpp_write(dev_t dev, struct uio *uio, int flags)
{
	return (sbpp_rw(dev, uio));
}

int
sbpp_rw(dev_t dev, struct uio *uio)
{
	return (ENXIO);
}

int
sbpp_poll(dev_t dev, int events, struct lwp *l)
{
	return (seltrue(dev, events, l));
}

int
sbpp_ioctl(dev_t dev, u_long cmd, void *data, int flags, struct lwp *l)
{
	int error;

	error = ENOTTY;

	return (error);
}

#endif /* NSPIF */
