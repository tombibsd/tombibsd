/*	$NetBSD$	*/

/*-
 * Copyright (c) 1999, 2001 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Jason R. Thorpe of the Numerical Aerospace Simulation Facility,
 * NASA Ames Research Center.
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

#ifndef _DEV_MII_NSPHYTERREG_H_
#define	_DEV_MII_NSPHYTERREG_H_

/*
 * DP83843 registers.  We also have the MacPHYTER (DP83815) internal
 * PHY register definitions here, since the two are, for our purposes,
 * compatible.
 */

#define	MII_NSPHYTER_PHYSTS	0x10	/* PHY status */
#define	PHYSTS_REL		0x8000	/* receive error latch */
#define	PHYSTS_CIML		0x4000	/* CIM latch */
#define	PHYSTS_FCSL		0x2000	/* false carrier sense latch */
#define	PHYSTS_DEVRDY		0x0800	/* device ready */
#define	PHYSTS_PGRX		0x0400	/* page received */
#define	PHYSTS_ANEGEN		0x0200	/* autoneg. enabled */
#define	PHYSTS_MIIINTR		0x0100	/* MII interrupt */
#define	PHYSTS_REMFAULT		0x0080	/* remote fault */
#define	PHYSTS_JABBER		0x0040	/* jabber detect */
#define	PHYSTS_NWAYCOMP		0x0020	/* NWAY complete */
#define	PHYSTS_RESETSTAT	0x0010	/* reset status */
#define	PHYSTS_LOOPBACK		0x0008	/* loopback status */
#define	PHYSTS_DUPLEX		0x0004	/* full duplex */
#define	PHYSTS_SPEED10		0x0002	/* speed == 10Mb/s */
#define	PHYSTS_LINK		0x0001	/* link up */
	/* below are the MacPHYTER bits that are different */
#define	PHYSTS_MP_REL		0x2000	/* receive error latch */
#define	PHYSTS_MP_POLARITY	0x1000	/* polarity inverted */
#define	PHYSTS_MP_FCSL		0x0800	/* false carrier sense latch */
#define	PHYSTS_MP_SIGNAL	0x0400	/* signal detect */
#define	PHYSTS_MP_DESCRLK	0x0200	/* de-scrambler lock */
#define	PHYSTS_MP_PGRX		0x0100	/* page received */
#define	PHYSTS_MP_MIIINTR	0x0080	/* MII interrupt */
#define	PHYSTS_MP_REMFAULT	0x0040	/* remote fault */
#define	PHYSTS_MP_JABBER	0x0020	/* jabber detect */
#define	PHYSTS_MP_NWAYCOMP	0x0010	/* NWAY complete */


#define	MII_NSPHYTER_MIPSCR	0x11	/* MII interrupt PHY specific
					   control */

#define	MIPSCR_INTEN		0x0002	/* interrupt enable */
#define	MIPSCR_TINT		0x0001	/* test interrupt */


#define	MII_NSPHYTER_MIPGSR	0x12	/* MII interrupt PHY generic
					   status */
#define	MIPGSR_MINT		0x8000	/* MII interrupt pending */
	/* below are MacPHYTER only */
#define	MIPGSR_MSK_LINK		0x4000	/* mask link status event */
#define	MIPGSR_MSK_JAB		0x2000	/* mask jabber event */
#define	MIPGSR_MSK_RF		0x1000	/* mask remote fault event */
#define	MIPGSR_MSK_ANC		0x0800	/* mask auto-neg complete event */
#define	MIPGSR_MSK_FHF		0x0400	/* mask false carrier half full event */
#define	MIPGSR_MSK_RHF		0x0200	/* mask rx error half full event */

#define	MII_NSPHYTER_DCR	0x13	/* Disconnect counter */

#define	MII_NSPHYTER_FCSCR	0x14	/* False carrier sense counter */

#define	MII_NSPHYTER_RECR	0x15	/* Receive error counter */


#define	MII_NSPHYTER_PCSR	0x16	/* PCS configuration and status */
#define	PCSR_SINGLE_SD		0x8000	/* single-ended SD mode */
#define	PCSR_FEFI_EN		0x4000	/* far end fault indication mode */
#define	PCSR_DESCR_TO_RST	0x2000	/* reset descrambler timeout counter */
#define	PCSR_DESCR_TO_SEL	0x1000	/* descrambler timer mode */
#define	PCSR_DESCR_TO_DIS	0x0800	/* descrambler timer disable */
#define	PCSR_LD_SCR_SD		0x0400	/* load scrambler seed */
#define	PCSR_TX_QUIET		0x0200	/* 100Mb/s transmit true quiet mode */
#define	PCSR_TX_PATTERN		0x0180	/* 100Mb/s transmit test pattern */
#define	PCSR_F_LINK_100		0x0040	/* force good link in 100Mb/s */
#define	PCSR_CIM_DIS		0x0020	/* carrier integrity monitor disable */
#define	PCSR_CIM_STATUS		0x0010	/* carrier integrity monitor status */
#define	PCSR_CODE_ERR		0x0008	/* code errors */
#define	PCSR_PME_ERR		0x0004	/* premature end errors */
#define	PCSR_LINK_ERR		0x0002	/* link errors */
#define	PCSR_PKT_ERR		0x0001	/* packet errors */
	/* below are the MacPHYTER bits that are different */
#define	PCSR_MP_BYP_4B5B	0x1000	/* bypass encoder */
#define	PCSR_MP_FREE_CLK	0x0800	/* free funning rx clock */
#define	PCSR_MP_TQ_EN		0x0400	/* enable True Quiet mode */
#define	PCSR_MP_SD_FORCE_B	0x0200	/* force signal detection */
#define	PCSR_MP_SD_OPTION	0x0100	/* enhanced signal detection alg. */
#define	PCSR_MP_NRZI_BYPASS	0x0004	/* NRZI bypass enabled */


	/* Not on MacPHYTER */
#define	MII_NSPHYTER_LBR	0x17	/* loopback and bypass */
#define	LBR_BP_STRETCH		0x4000	/* bypass LED stretching */
#define	LBR_BP_4B5B		0x2000	/* bypass encoding/decoding */
#define	LBR_BP_SCR		0x1000	/* bypass scrambler/descrambler */
#define	LBR_BP_RX		0x0800	/* bypass receive function */
#define	LBR_BP_TX		0x0400	/* bypass transmit function */
#define	LBR_100_DP_CTL		0x0380	/* 100Mb/s data patch control */
#define	LBR_TW_LBEN		0x0020	/* TWISTER loopback enable */
#define	LBR_10_ENDEC_LB		0x0010	/* 10Mb/s ENDEC loopback */


	/* Not on MacPHYTER */
#define	MII_NSPHYTER_10BTSCR	0x18	/* 10baseT status and control */
#define	BTSCR_AUI_TPI		0x2000	/* TREX operating mode */
#define	BTSCR_RX_SERIAL		0x1000	/* 10baseT RX serial mode */
#define	BTSCR_TX_SERIAL		0x0800	/* 10baseT TX serial mode */
#define	BTSCR_POL_DS		0x0400	/* polarity detection and correction
					   disable */
#define	BTSCR_AUTOSW_EN		0x0200	/* AUI/TPI autoswitch */
#define	BTSCR_LP_DS		0x0100	/* link pulse disable */
#define	BTSCR_HB_DS		0x0080	/* heartbeat disabled */
#define	BTSCR_LS_SEL		0x0040	/* low squelch select */
#define	BTSCR_AUI_SEL		0x0020	/* AUI select */
#define	BTSCR_JAB_DS		0x0010	/* jabber disable */
#define	BTSCR_THIN_SEL		0x0008	/* thin ethernet select */
#define	BTSCR_TX_FILT_DS	0x0004	/* TPI receive filter disable */


#define	MII_NSPHYTER_PHYCTRL	0x19	/* PHY control */
#define	PHYCTRL_TW_EQSEL	0x3000	/* TWISTER e.q. select */
#define	PHYCTRL_BLW_DS		0x0800	/* TWISTER base line wander disable */
#define	PHYCTRL_REPEATER	0x0200	/* repeater mode */
#define	PHYCTRL_LED_TXRX_MODE	0x0180	/* LED TX/RX mode */
#define	PHYCTRL_LED_DUP_MODE	0x0040	/* LED DUP mode */
#define	PHYCTRL_FX_EN		0x0020	/* Fiber mode enable */
#define	PHYCTRL_PHYADDR		0x001f	/* PHY address */
	/* below are the MacPHYTER bits that are different */
#define	PHYCRTL_MP_PSR_15	0x0800	/* BIST sequence select */
#define	PHYCTRL_MP_BIST_STAT	0x0400	/* BIST passed */
#define	PHYCTRL_MP_BIST_START	0x0200	/* start BIST */
#define	PHYCTRL_MP_BP_STRETCH	0x0100	/* bypass LED stretching */
#define	PHYCTRL_MP_PAUSE_STS	0x0080	/* pause status */


	/* MacPHYTER only */
#define	MII_MACPHYTER_TBTCTL	0x1a	/* 10baseT Control */
#define	TBTCTL_LOOPBACK_10_DIS	0x0100	/* loopback 10Mb/s disable */
#define	TBTCTL_LP_DIS		0x0080	/* link pulse disable */
#define	TBTCTL_FORCE_LINK_10	0x0040	/* force 10Mb/s link good */
#define	TBTCTL_FORCE_POL_COR	0x0020	/* force polarity correction */
#define	TBTCTL_INV_POLARITY	0x0010	/* inverted polarity */
#define	TBTCTL_AUTOPOL_DIS	0x0008	/* auto-polarity disable */
#define	TBTCTL_HEARTBEAT_DIS	0x0002	/* heartbeat disable */
#define	TBTCTL_JABBER_DIS	0x0001	/* jabber disable */

#endif /* _DEV_MII_NSPHYTERREG_H_ */
