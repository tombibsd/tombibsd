/*	$NetBSD$	*/
/*	$OpenBSD: apmvar.h,v 1.2 2001/10/03 20:06:01 drahn Exp $	*/

/*
 *  Copyright (c) 2001 Alexander Guy
 *  Copyright (c) 1995 John T. Kohl
 *  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR `AS IS'' AND ANY EXPRESS OR
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
 */
#ifndef _MACPPC_APMVAR_H_
#define _MACPPC_APMVAR_H_

#include <sys/ioccom.h>

/* Advanced Power Management (v1.0 and v1.1 specification)
 * functions/defines/etc.
 */

/* These definitions make up the heart of the user-land interface
 * to the APM devices.
 */

#define		APM_AC_OFF		0x00
#define		APM_AC_ON		0x01
#define		APM_AC_BACKUP		0x02
#define		APM_AC_UNKNOWN		0xff
#define		APM_BATT_HIGH		0x00
#define		APM_BATT_LOW		0x01
#define		APM_BATT_CRITICAL	0x02
#define		APM_BATT_CHARGING	0x03
#define		APM_BATT_ABSENT		0x04 /* Software only--not in spec! */
#define		APM_BATT_UNKNOWN	0xff
#define		APM_BATT_LIFE_UNKNOWN	0xff

#define		APM_NOEVENT		0x0000
#define		APM_STANDBY_REQ		0x0001 
#define		APM_SUSPEND_REQ		0x0002
#define		APM_NORMAL_RESUME	0x0003
#define		APM_CRIT_RESUME		0x0004 /* suspend/resume happened
						  without us */
#define		APM_BATTERY_LOW		0x0005
#define		APM_POWER_CHANGE	0x0006
#define		APM_UPDATE_TIME		0x0007
#define		APM_CRIT_SUSPEND_REQ	0x0008
#define		APM_USER_STANDBY_REQ	0x0009
#define		APM_USER_SUSPEND_REQ	0x000A
#define		APM_SYS_STANDBY_RESUME	0x000B
#define		APM_CAPABILITY_CHANGE	0x000C	/* apm v1.2 */
#define		APM_EVENT_MASK		0xffff

#define	APM_EVENT_COMPOSE(t,i)	((((i) & 0x7fff) << 16)|((t) & APM_EVENT_MASK))
#define	APM_EVENT_TYPE(e)	((e) & APM_EVENT_MASK)
#define	APM_EVENT_INDEX(e)	((e) >> 16)

#include <dev/apm/apmio.h>

#define APM_BATTERY_ABSENT 4

#define APM_IOC_PRN_CTL _IOW('A', 6, int ) /* driver power status msg */
#define		APM_PRINT_ON	0	/* driver power status displayed */
#define		APM_PRINT_OFF	1	/* driver power status not displayed */
#define		APM_PRINT_PCT	2	/* driver power status only displayed
					   if the percentage changes */

#endif /* _MACPPC_APMVAR_H_ */
