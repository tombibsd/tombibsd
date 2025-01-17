/*	$NetBSD$	*/
/*	$OpenBSD: if_maloreg.h,v 1.15 2007/10/08 22:08:12 mglocker Exp $ */

/*
 * Copyright (c) 2007 Marcus Glocker <mglocker@openbsd.org>
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

#define MALO_REG_INT_CODE			0x00000C14
/* From host to ARM */
#define MALO_REG_H2A_INTERRUPT_EVENTS		0x00000C18

/* bit definitions for MALO_REG_H2A_INTERRUPT_CAUSE */
#define MALO_H2ARIC_BIT_PPA_READY		0x00000001
#define MALO_H2ARIC_BIT_DOOR_BELL		0x00000002 /* bit 1 */
#define MALO_H2ARIC_BIT_PS			0x00000004
#define MALO_H2ARIC_BIT_PSPOLL			0x00000008 /* bit 3 */

/* From ARM to host */
#define MALO_REG_A2H_INTERRUPT_CAUSE		0x00000C30
#define MALO_REG_A2H_INTERRUPT_MASK		0x00000C34
#define MALO_REG_A2H_INTERRUPT_CLEAR_SEL	0x00000C38
#define MALO_REG_A2H_INTERRUPT_STATUS_MASK	0x00000C3C

/* bit definitions for MALO_REG_A2H_INTERRUPT_CAUSE */
#define MALO_A2HRIC_BIT_TX_DONE			0x00000001	/* bit 0 */
#define MALO_A2HRIC_BIT_RX_RDY			0x00000002	/* bit 1 */
#define MALO_A2HRIC_BIT_OPC_DONE		0x00000004
#define MALO_A2HRIC_BIT_MAC_EVENT		0x00000008
#define MALO_A2HRIC_BIT_RX_PROBLEM		0x00000010
#define MALO_A2HRIC_BIT_RADIO_OFF		0x00000020	/* bit 5 */
#define MALO_A2HRIC_BIT_RADIO_ON		0x00000040
#define MALO_A2HRIC_BIT_RADAR_DETECT		0x00000080
#define MALO_A2HRIC_BIT_ICV_ERROR		0x00000100
#define MALO_A2HRIC_BIT_MIC_ERROR		0x00000200	/* bit 9 */
#define MALO_A2HRIC_BIT_QUEUE_EMPTY		0x00000400
#define MALO_A2HRIC_BIT_QUEUE_FULL		0x00000800
#define MALO_A2HRIC_BIT_CHAN_SWITCH		0x00001000
#define MALO_A2HRIC_BIT_TX_WATCHDOG		0x00002000
#define MALO_A2HRIC_BIT_BA_WATCHDOG		0x00004000

#define MALO_ISR_SRC_BITS			\
	(MALO_A2HRIC_BIT_RX_RDY |		\
	 MALO_A2HRIC_BIT_TX_DONE |		\
	 MALO_A2HRIC_BIT_OPC_DONE |		\
	 MALO_A2HRIC_BIT_MAC_EVENT |		\
	 MALO_A2HRIC_BIT_MIC_ERROR |		\
	 MALO_A2HRIC_BIT_ICV_ERROR |		\
	 MALO_A2HRIC_BIT_RADAR_DETECT |		\
	 MALO_A2HRIC_BIT_CHAN_SWITCH |		\
	 MALO_A2HRIC_BIT_TX_WATCHDOG |		\
	 MALO_A2HRIC_BIT_QUEUE_EMPTY)
#define MALO_ISR_RESET				(1<<15)

#define MALO_A2HRIC_BIT_MASK			MALO_ISR_SRC_BITS

/* map to 0x80000000 on BAR1  */
#define MALO_REG_GEN_PTR			0x00000C10
#define MALO_REG_INT_CODE			0x00000C14
#define MALO_REG_SCRATCH			0x00000C40

/*
 * define OpMode for SoftAP/Station mode
 *
 * the following mode signature has to be written to PCI scratch register#0
 * right after successfully downloading the last block of firmware and
 * before waiting for firmware ready signature
 */
#define MALO_HOSTCMD_STA_MODE			0x5A
#define MALO_HOSTCMD_STA_FWRDY_SIGNATURE	0xF0F1F2F4

/*
 * 16 bit host command code
 */
#define MALO_HOSTCMD_NONE			0x0000
#define MALO_HOSTCMD_CODE_DNLD			0x0001
#define MALO_HOSTCMD_GET_HW_SPEC		0x0003
#define MALO_HOSTCMD_SET_HW_SPEC		0x0004
#define MALO_HOSTCMD_MAC_MULTICAST_ADR		0x0010
#define MALO_HOSTCMD_SET_WEPKEY			0x0013
#define MALO_HOSTCMD_802_11_RADIO_CONTROL	0x001c
#define MALO_HOSTCMD_802_11_RF_TX_POWER		0x001e
#define MALO_HOSTCMD_802_11_RF_ANTENNA		0x0020
#define MALO_HOSTCMD_SET_PRE_SCAN		0x0107
#define MALO_HOSTCMD_SET_POST_SCAN		0x0108
#define MALO_HOSTCMD_SET_RF_CHANNEL		0x010a
#define MALO_HOSTCMD_SET_AID			0x010d
#define MALO_HOSTCMD_SET_RATE			0x0110
#define MALO_HOSTCMD_SET_SLOT			0x0114
/* define DFS lab commands  */
#define MALO_HOSTCMD_SET_FIXED_RATE		0x0126 
#define MALO_HOSTCMD_SET_REGION_POWER		0x0128
#define MALO_HOSTCMD_GET_CALTABLE		0x1134

/*
 * definition of action or option for each command.
 */
/* define general purpose action  */
#define MALO_HOSTCMD_ACT_GEN_GET		0x0000
#define MALO_HOSTCMD_ACT_GEN_SET		0x0001
#define MALO_HOSTCMD_ACT_GEN_SET_LIST		0x0002

/* define action or option for HostCmd_FW_USE_FIXED_RATE */
#define MALO_HOSTCMD_ACT_USE_FIXED_RATE		0x0001
#define MALO_HOSTCMD_ACT_NOT_USE_FIXED_RATE	0x0002

/* INT code register event definition  */
#define MALO_INT_CODE_CMD_FINISHED		0x00000005
