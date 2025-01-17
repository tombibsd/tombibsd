/*	$NetBSD$	*/

/*-
 * Copyright (c) 1999 Izumi Tsutsui.  All rights reserved.
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

/* DMAC 266 register definition */

struct dma_regs {
	volatile uint32_t ctl;			/* Control Register	*/
#define	 DC_CTL_RST	0x04			/* Soft Reset		*/
#define	 DC_CTL_MOD	0x02			/* set transfer dir	*/
#define	 DC_CTL_ENB	0x01			/* set Enable		*/

	volatile uint32_t stat;			/* Status Register 	*/
#define	 DC_ST_TCZ	0x10			/* Transfer Count Zero 	*/
#define	 DC_ST_INT	0x08			/* Interrupt 		*/
#define	 DC_ST_MOD	0x02			/* monitor transfer dir	*/
#define	 DC_ST_ENB	0x01			/* monitor Enable	*/

	volatile uint32_t tcnt;			/* transfer counter	*/
	volatile uint32_t tag;			/* Tag Register 	*/
	volatile uint32_t offset;		/* Offset Register 	*/
	volatile uint32_t mapent;		/* Map entry Register 	*/
};

#define DMAC_WAIT	__asm volatile ("nop; nop; nop; nop; nop; nop")

#define DMAC_SEG_SIZE	0x1000 /* 4kbyte per DMA segment */
#define DMAC_SEG_OFFSET	0x0fff
#define DMAC_SEG_SHIFT	12
