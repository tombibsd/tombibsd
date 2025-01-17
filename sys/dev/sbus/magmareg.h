/*	$NetBSD$	*/

/*-
 *  Copyright (c) 1998 Iain Hibbert
 *  All rights reserved.
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

#ifdef MAGMA_DEBUG
#define dprintf(x) printf x
#else
#define dprintf(x)
#endif

/*  The mapping of minor device number -> card and port is done as
 * follows by default:
 *
 *  +---+---+---+---+---+---+---+---+
 *  | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 *  +---+---+---+---+---+---+---+---+
 *    |   |   |   |   |   |   |   |
 *    |   |   |   |   +---+---+---+---> port number
 *    |   |   |   |
 *    |   |   |   +-------------------> unused
 *    |   |   |
 *    |   |   +-----------------------> unused
 *    |   |
 *    +---+---------------------------> card number
 *
 */

#define MAGMA_MAX_CARDS		4
#define MAGMA_MAX_TTY		16
#define MAGMA_MAX_BPP		2
#define MAGMA_MAX_CD1400	4
#define MAGMA_MAX_CD1190	2

#define MAGMA_CARD(x)	((TTUNIT(x) >> 6) & 0x03)
#define MAGMA_PORT(x)	(TTUNIT(x) & 0x0f)

#define MTTY_DIALOUT(x) TTDIALOUT(x)

/*
 * Supported Card Types
 */
struct magma_board_info {
	const char *mb_sbusname;	/* sbus_attach_args.sa_name */
	const char *mb_name;		/* cardname to match against */
	const char *mb_realname;	/* english card name */
	int mb_nser;			/* number of serial ports */
	int mb_npar;			/* number of parallel ports */
	int mb_ncd1400;			/* number of CD1400 chips */
	int mb_svcackr;			/* svcackr offset */
	int mb_svcackt;			/* svcackt offset */
	int mb_svcackm;			/* svcackm offset */
	int mb_cd1400[MAGMA_MAX_CD1400];/* cd1400 chip register offsets */
	int mb_ncd1190;			/* number of CD1190 chips */
	int mb_cd1190[MAGMA_MAX_CD1190];/* cd1190 chip register offsets */
};

/*
 * cd1400 chip data
 */
struct cd1400 {
	volatile u_char *cd_reg;	/* chip registers */
	int cd_chiprev;			/* chip revision */
	int cd_clock;			/* clock speed in MHz */
	int cd_parmode;			/* parallel mode operation */
};

/*
 * cd1190 chip data
 */
struct cd1190 {
	volatile u_char *cd_reg;	/* chip registers */
	int cd_chiprev;			/* chip revision */
};

/* software state for each card */
struct magma_softc {
	device_t	ms_dev;		/* required. must be first in softc */
	struct evcnt	ms_intrcnt;	/* statistics */

	/* cd1400 chip info */
	int	ms_ncd1400;
	struct cd1400 ms_cd1400[MAGMA_MAX_CD1400];
	volatile u_char *ms_svcackr;	/* CD1400 service acknowledge receive */
	volatile u_char *ms_svcackt;	/* CD1400 service acknowledge transmit */
	volatile u_char *ms_svcackm;	/* CD1400 service acknowledge modem */

	/* cd1190 chip info */
	int ms_ncd1190;
	struct cd1190 ms_cd1190[MAGMA_MAX_CD1190];

	struct magma_board_info *ms_board;	/* what am I? */

	struct mtty_softc *ms_mtty;
	struct mbpp_softc *ms_mbpp;

	/* softintr(9) cookie */
	void	*ms_sicookie;
};

#define MTTY_RBUF_SIZE		(2 * 512)
#define MTTY_RX_FIFO_THRESHOLD	6
#define MTTY_RX_DTR_THRESHOLD	9

struct mtty_port {
	struct cd1400 *mp_cd1400;	/* ptr to chip */
	int mp_channel;			/* and channel */
	struct tty *mp_tty;

	int mp_openflags;	/* default tty flags */
	int mp_flags;		/* port flags */
	int mp_carrier;		/* state of carrier */

	u_char *mp_rbuf;	/* ring buffer start */
	u_char *mp_rend;	/* ring buffer end */
	u_char *mp_rget;	/* ring buffer read pointer */
	u_char *mp_rput;	/* ring buffer write pointer */

	u_char *mp_txp;		/* transmit character pointer */
	int mp_txc;		/* transmit character counter */
};

#define MTTYF_CARRIER_CHANGED	(1<<0)
#define MTTYF_SET_BREAK		(1<<1)
#define MTTYF_CLR_BREAK		(1<<2)
#define MTTYF_DONE		(1<<3)
#define MTTYF_STOP		(1<<4)
#define MTTYF_RING_OVERFLOW	(1<<5)

struct mtty_softc {
	device_t ms_dev;		/* device info */
	int ms_nports;			/* tty ports */
	struct mtty_port ms_port[MAGMA_MAX_TTY];
};

#define MBPP_RX_FIFO_THRESHOLD	25

struct mbpp_port {
	struct cd1400 *mp_cd1400;	/* for LC2+1Sp card */
	struct cd1190 *mp_cd1190;	/* all the others   */

	struct callout mp_timeout_ch;
	struct callout mp_start_ch;

	int	mp_flags;

	struct mbpp_param mp_param;
#define mp_burst	mp_param.bp_burst
#define mp_timeout	mp_param.bp_timeout
#define mp_delay	mp_param.bp_delay

	u_char	*mp_ptr;		/* pointer to I/O data */
	int	mp_cnt;			/* count of I/O chars */
};

#define MBPPF_OPEN	(1<<0)
#define MBPPF_TIMEOUT	(1<<1)
#define MBPPF_UIO	(1<<2)
#define MBPPF_DELAY	(1<<3)
#define MBPPF_WAKEUP	(1<<4)

struct mbpp_softc {
	int ms_nports;			/* parallel ports */
	struct mbpp_port ms_port[MAGMA_MAX_BPP];
};

/*
 * useful macros
 */
#define SET(t, f)	((t) |= (f))
#define CLR(t, f)	((t) &= ~(f))
#define ISSET(t, f)	((t) & (f))

/* internal function prototypes */

int cd1400_compute_baud(speed_t, int, int *, int *);
__inline void cd1400_write_ccr(struct cd1400 *, u_char);
__inline u_char cd1400_read_reg(struct cd1400 *, int);
__inline void cd1400_write_reg(struct cd1400 *, int, u_char);
void cd1400_enable_transmitter(struct cd1400 *, int);

int magma_match(device_t, cfdata_t, void *);
void magma_attach(device_t, device_t, void *);
int magma_hard(void *);
void magma_soft(void *);

int mtty_match(device_t, cfdata_t, void *);
void mtty_attach(device_t, device_t, void *);
int mtty_modem_control(struct mtty_port *, int, int);
int mtty_param(struct tty *, struct termios *);
void mtty_start(struct tty *);

int mbpp_match(device_t, cfdata_t, void *);
void mbpp_attach(device_t, device_t, void *);
void mbpp_timeout(void *);
void mbpp_start(void *);
int mbpp_send(struct mbpp_port *, void *, int);
int mbpp_recv(struct mbpp_port *, void *, int);
int mbpp_hztoms(int);
int mbpp_mstohz(int);
