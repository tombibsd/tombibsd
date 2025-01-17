/*	$NetBSD$	*/
/*	$OpenBSD: sdmmc_ioreg.h,v 1.4 2007/06/02 01:48:37 uwe Exp $	*/

/*
 * Copyright (c) 2006 Uwe Stuehler <uwe@openbsd.org>
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

#ifndef	_SDMMC_IOREG_H_
#define	_SDMMC_IOREG_H_

/* SDIO commands */				/* response type */
#define SD_IO_SEND_OP_COND		5	/* R4 */
#define SD_IO_RW_DIRECT			52	/* R5 */
#define SD_IO_RW_EXTENDED		53	/* R5? */

/* CMD52 arguments */
#define SD_ARG_CMD52_READ		(0<<31)
#define SD_ARG_CMD52_WRITE		(1<<31)
#define SD_ARG_CMD52_FUNC_SHIFT		28
#define SD_ARG_CMD52_FUNC_MASK		0x7
#define SD_ARG_CMD52_EXCHANGE		(1<<27)
#define SD_ARG_CMD52_REG_SHIFT		9
#define SD_ARG_CMD52_REG_MASK		0x1ffff
#define SD_ARG_CMD52_DATA_SHIFT		0
#define SD_ARG_CMD52_DATA_MASK		0xff
#define SD_R5_DATA(resp)		((resp)[0] & 0xff)

/* CMD53 arguments */
#define SD_ARG_CMD53_READ		(0<<31)
#define SD_ARG_CMD53_WRITE		(1<<31)
#define SD_ARG_CMD53_FUNC_SHIFT		28
#define SD_ARG_CMD53_FUNC_MASK		0x7
#define SD_ARG_CMD53_BLOCK_MODE		(1<<27)
#define SD_ARG_CMD53_INCREMENT		(1<<26)
#define SD_ARG_CMD53_REG_SHIFT		9
#define SD_ARG_CMD53_REG_MASK		0x1ffff
#define SD_ARG_CMD53_LENGTH_SHIFT	0
#define SD_ARG_CMD53_LENGTH_MASK	0x1ff
#define SD_ARG_CMD53_LENGTH_MAX		64 /* XXX should be 511? */

/* 48-bit response decoding (32 bits w/o CRC) */
#define MMC_R4(resp)			((resp)[0])
#define MMC_R5(resp)			((resp)[0])

/* SD R4 response (IO OCR) */
#define SD_IO_OCR_MEM_READY		(1<<31)
#define SD_IO_OCR_NUM_FUNCTIONS(ocr)	(((ocr) >> 28) & 0x7)
#define SD_IO_OCR_MEM_PRESENT		(1<<27)
#define SD_IO_OCR_MASK			0x00fffff0

/* Card Common Control Registers (CCCR) */
#define SD_IO_CCCR_START		0x00000
#define SD_IO_CCCR_SIZE			0x100
#define SD_IO_CCCR_CCCR_SDIO_REV	0x00
#define SD_IO_CCCR_CCCR_REV(r)		((r) & 0xf)
#define  CCCR_CCCR_REV_1_00		0
#define  CCCR_CCCR_REV_1_10		1
#define  CCCR_CCCR_REV_1_20		2
#define SD_IO_CCCR_SDIO_REV(r)		(((r) >> 4) & 0xf)
#define  CCCR_SDIO_REV_1_00		0
#define  CCCR_SDIO_REV_1_10		1
#define  CCCR_SDIO_REV_1_20		2	/* (unreleased) */
#define  CCCR_SDIO_REV_2_00		3
#define SD_IO_CCCR_SPEC_REV		0x01
#define SD_IO_CCCR_SD_PHYS_SPEC_VER(r)	((r) & 0xf)
#define  CCCR_SD_PHYS_SPEC_VER_1_01	0
#define  CCCR_SD_PHYS_SPEC_VER_1_10	1
#define  CCCR_SD_PHYS_SPEC_VER_2_00	2
#define SD_IO_CCCR_FN_ENABLE		0x02
#define SD_IO_CCCR_FN_IOREADY		0x03
#define SD_IO_CCCR_FN_INTEN		0x04
#define  CCCR_INTEN_INTM		(1<<0)
#define SD_IO_CCCR_FN_INTPENDING	0x05
#define SD_IO_CCCR_CTL			0x06
#define  CCCR_CTL_RES			(1<<3)
#define SD_IO_CCCR_BUS_WIDTH		0x07
#define  CCCR_BUS_WIDTH_4		(2<<0)
#define  CCCR_BUS_WIDTH_1		(0<<0)
#define SD_IO_CCCR_CAPABILITY		0x08
#define  CCCR_CAPS_SDC			(1<<0)
#define  CCCR_CAPS_SMB			(1<<1) /* Multi-Block support */
#define  CCCR_CAPS_SRB			(1<<2) /* Read Wait support */
#define  CCCR_CAPS_SBS			(1<<3) /* Suspend/Resume support */
#define  CCCR_CAPS_S4MI			(1<<4) /* intr support in 4-bit mode */
#define  CCCR_CAPS_E4MI			(1<<5) /* enable intr in 4-bit mode */
#define  CCCR_CAPS_LSC			(1<<6) /* Low speed card */
#define  CCCR_CAPS_4BLS			(1<<7) /* 4-bit support for low speed */
#define SD_IO_CCCR_CISPTR		0x09 /* XXX 9-10, 10-11, or 9-12 */
#define SD_IO_CCCR_BUS_SUSPEND		0x0c
#define SD_IO_CCCR_FUNC_SELECT		0x0d
#define  CCCR_FUNC_FS(r)		((r) & 0xf)
#define  CCCR_FUNC_FS_FN(fn)		((fn) & 0x7)
#define  CCCR_FUNC_FS_MEM		8
#define SD_IO_CCCR_FN_EXEC_FLG		0x0e
#define SD_IO_CCCR_FN_READY_FLG		0x0f
#define SD_IO_CCCR_FN0_BLKSIZ		0x10 /* 0x10-0x11 */
#define SD_IO_CCCR_POWER_CTL		0x12
#define SD_IO_CCCR_HIGH_SPEED		0x13
#define  CCCR_HIGH_SPEED_SHS		(1<<0) /* Support High-Speed */
#define  CCCR_HIGH_SPEED_EHS		(1<<1) /* Enable High-Speed */

/* Function Basic Registers (FBR) */
#define SD_IO_FBR_START			0x00100
#define SD_IO_FBR_SIZE			0x100
#define SD_IO_FBR(func)	((((func) - 1) * SD_IO_FBR_SIZE) + SD_IO_FBR_START)
#define  FBR_STD_FUNC_IF_CODE(v)	((v) & 0x0f)

/* Card Information Structure (CIS) */
#define SD_IO_CIS_START			0x01000
#define SD_IO_CIS_SIZE			0x17000

/* SDIO Standard Function Interface code */
#define SD_IO_SFIC_NO_STANDARD		0x0
#define SD_IO_SFIC_UART			0x1
#define SD_IO_SFIC_TYPEA_BLUETOOTH	0x2	/* Type-A Bluetooth */
#define SD_IO_SFIC_TYPEB_BLUETOOTH	0x3	/* Type-B Bluetooth */
#define SD_IO_SFIC_GPS			0x4
#define SD_IO_SFIC_CAMERA		0x5
#define SD_IO_SFIC_PHS			0x6
#define SD_IO_SFIC_WLAN			0x7
#define SD_IO_SFIC_ATA			0x8	/* Embedded SDIO-ATA */

#endif	/* _SDMMC_IOREG_H_ */
