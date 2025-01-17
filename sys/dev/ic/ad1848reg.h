/*	$NetBSD$	*/

/*
 * Copyright (c) 1994 John Brezak
 * Copyright (c) 1991-1993 Regents of the University of California.
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
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the Computer Systems
 *	Engineering Group at Lawrence Berkeley Laboratory.
 * 4. Neither the name of the University nor of the Laboratory may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
/*
 * Copyright (c) 1993 Analog Devices Inc. All rights reserved
 */

/* parent driver is primarily responsible for checking this */
#define AD1848_BASE_VALID(base)	(((base) & 0x003) == 0)

/* AD1848 direct registers */
#define AD1848_IADDR		0x00
#define AD1848_IDATA		0x01
#define AD1848_STATUS		0x02
#define AD1848_PIO		0x03

/* Gain constants  */
#define GAIN_0			0x00
#define GAIN_1_5		0x01
#define GAIN_3			0x02
#define GAIN_4_5		0x03
#define GAIN_6			0x04
#define GAIN_7_5		0x05
#define GAIN_9			0x06
#define GAIN_10_5		0x07
#define GAIN_12			0x08
#define GAIN_13_5		0x09
#define GAIN_15			0x0a
#define GAIN_16_5		0x0b
#define GAIN_18			0x0c
#define GAIN_19_5		0x0d
#define GAIN_21			0x0e
#define GAIN_22_5		0x0f

/* Attenuation constants  */

#define ATTEN_0			0x00
#define ATTEN_1_5		0x01
#define ATTEN_3			0x02
#define ATTEN_4_5		0x03
#define ATTEN_6			0x04
#define ATTEN_7_5		0x05
#define ATTEN_9			0x06
#define ATTEN_10_5		0x07
#define ATTEN_12		0x08
#define ATTEN_13_5		0x09
#define ATTEN_15		0x0a
#define ATTEN_16_5		0x0b
#define ATTEN_18		0x0c
#define ATTEN_19_5		0x0d
#define ATTEN_21		0x0e
#define ATTEN_22_5		0x0f

/* AD1848 Index register (R0) */
#define SP_IN_INIT		0x80
#define MODE_CHANGE_ENABLE	0x40
#define TRANSFER_DISABLE	0x20
#define ADDRESS_MASK		0xe0

/* Status bits - register R2 (read-only) */
#define INTERRUPT_STATUS	0x01
#define PLAYBACK_READY		0x02
#define PLAYBACK_LEFT		0x04
/* pbright is not left */
#define PLAYBACK_UPPER		0x08
/* bplower is not upper */
#define SAMPLE_ERROR		0x10
#define CAPTURE_READY		0x20
#define CAPTURE_LEFT		0x40
/* cpright is not left */
#define CAPTURE_UPPER		0x80
/* cplower is not upper */

#define AD_R2_BITS	"\20\1INT\2PRDY\3PL/R\4PU/L\5SER\6CRDY\7CL/R\10CU/L"


/* ADC Input control - registers I0 (left) and I1 (right) */
#define LINE_INPUT		0x00
#define AUX_INPUT		0x40
#define MIC_INPUT		0x80
#define MIXED_DAC_INPUT		0xc0
#define INPUT_GAIN_MASK		0xf0
#define INPUT_MIC_GAIN_ENABLE	0x20
#define INPUT_SOURCE_MASK	0x3f

/* Aux input control - registers I2 (channel 1,left); I3 (channel 1,right)
				 I4 (channel 2,left); I5 (channel 2,right) */
#define AUX_INPUT_ATTEN_BITS	0x1f
#define AUX_INPUT_ATTEN_MASK	0xe0
#define AUX_INPUT_MUTE		0x80

/* Output bits - registers I6,I7*/
#define OUTPUT_MUTE		0x80
#define OUTPUT_ATTEN_BITS	0x3f
#define OUTPUT_ATTEN_MASK	(~OUTPUT_ATTEN_BITS & 0xff)

/* Clock and Data format reg bits (some also Capture Data format) - reg I8 */
#define CLOCK_XTAL2		0x01
#define CLOCK_XTAL1		0x00
#define CLOCK_FREQ_MASK		0xf1
#define FMT_MONO		0x00
#define FMT_STEREO		0x10
#define FORMAT_MASK		0x1f
#define FMT_PCM8		0x00	/* 8-bit unsigned */
#define FMT_ULAW		0x20	/* 8-bit mu-law */
#define FMT_TWOS_COMP		0x40	/* 16-bit signed */
#define FMT_ALAW		0x60	/* 8-bit A-law */
#define FMT_ADPCM		0xa0	/* IMA ADPCM */
#define FMT_TWOS_COMP_BE	0xc0	/* 16-bit signed, big endian */

/* Interface Configuration reg bits - register I9 */
#define PLAYBACK_ENABLE		0x01
#define CAPTURE_ENABLE		0x02
#define DUAL_DMA		0x00
#define SINGLE_DMA		0x04
#define AUTO_CAL_ENABLE		0x08
#define PLAYBACK_PIO_ENABLE	0x40
#define CAPTURE_PIO_ENABLE	0x80

/* Pin control bits - register I10 */
#define INTERRUPT_ENABLE	0x02
#define XCTL0_ENABLE		0x40
#define XCTL1_ENABLE		0x80

/* Test and init reg bits - register I11 (read-only) */
#define OVERRANGE_LEFT_MASK	0xfc
#define OVERRANGE_RIGHT_MASK	0xf3
#define DATA_REQUEST_STATUS	0x10
#define AUTO_CAL_IN_PROG	0x20
#define PLAYBACK_UNDERRUN	0x40
#define CAPTURE_OVERRUN		0x80

/* Miscellaneous Control reg bits - register I12 */
#define ID_MASK			0x70
#define MODE2			0x40
#define MODE3			0x60

/* Digital Mix Control reg bits - register I13 */
#define DIGITAL_MIX1_ENABLE	0x01
#define MIX_ATTEN_MASK		0x03

/* AD1848 Sound Port reg defines */
#define SP_LEFT_INPUT_CONTROL	0
#define SP_RIGHT_INPUT_CONTROL	1
#define SP_LEFT_AUX1_CONTROL	2
#define SP_RIGHT_AUX1_CONTROL	3
#define SP_LEFT_AUX2_CONTROL	4
#define SP_RIGHT_AUX2_CONTROL	5
#define SP_LEFT_OUTPUT_CONTROL	6
#define SP_RIGHT_OUTPUT_CONTROL 7
#define SP_CLOCK_DATA_FORMAT	8
#define SP_INTERFACE_CONFIG	9
#define SP_PIN_CONTROL		10
#define SP_TEST_AND_INIT	11
#define SP_MISC_INFO		12
#define SP_DIGITAL_MIX		13
#define SP_UPPER_BASE_COUNT	14
#define SP_LOWER_BASE_COUNT	15

#define SP_IADDR_MASK		0xaf
