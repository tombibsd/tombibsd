/*	$NetBSD$	*/

/* Copyright 1988,1990,1993,1994 by Paul Vixie
 * All rights reserved
 */

/*
 * Copyright (c) 2004 by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1997,2000 by Internet Software Consortium, Inc.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* config.h - configurables for ISC Cron
 *
 * Id: config.h,v 1.10 2004/01/23 18:56:42 vixie Exp
 */

/*
 * these are site-dependent
 */

#ifndef DEBUGGING
#define DEBUGGING 1	/* 1 or 0 -- do you want debugging code built in? */
#endif

			/*
			 * choose one of these mailer commands.  some use
			 * /bin/mail for speed; it makes biff bark but doesn't
			 * do aliasing.  sendmail does do aliasing but is
			 * a hog for short messages.  aliasing is not needed
			 * if you make use of the MAILTO= feature in crontabs.
			 * (hint: MAILTO= was added for this reason).
			 */

#define MAILFMT "%s -FCronDaemon -odi -oem -oi -t" /*-*/
			/* -Fx	 = Set full-name of sender
			 * -odi	 = Option Deliverymode Interactive
			 * -oem	 = Option Errors Mailedtosender
			 * -oi   = Ignore "." alone on a line
			 * -t    = read recipient from header of message
			 */
#define MAILARG _PATH_SENDMAIL				/*-*/

/* #define MAILFMT "%s -d %s"				*/
			/* -d = undocumented but common flag: deliver locally?
			 */
/* #define MAILARG "/bin/mail",mailto			*/

/* #define MAILFMT "%s -mlrxto %s"			*/
/* #define MAILARG "/usr/mmdf/bin/submit",mailto	*/

/* #define MAIL_DATE				*/
			/* should we include an ersatz Date: header in
			 * generated mail?  if you are using sendmail
			 * as the mailer, it is better to let sendmail
			 * generate the Date: header.
			 */

			/* if you want to use syslog(3) instead of appending
			 * to CRONDIR/LOG_FILE (/var/cron/log, e.g.), define
			 * SYSLOG here.  Note that quite a bit of logging
			 * info is written, and that you probably don't want
			 * to use this on 4.2bsd since everything goes in
			 * /usr/spool/mqueue/syslog.  On 4.[34]bsd you can
			 * tell /etc/syslog.conf to send cron's logging to
			 * a separate file.
			 *
			 * Note that if this and LOG_FILE in "pathnames.h"
			 * are both defined, then logging will go to both
			 * places.
			 */
#define SYSLOG	 			/*-*/

			/* if you want cron to capitalize its name in ps
			 * when running a job.  Does not work on SYSV.
			 */
/* #define CAPITALIZE_FOR_PS		*/

			/* if you have a tm_gmtoff member in struct tm.
			 * If not, we will have to compute the value ourselves.
			 */
#define HAVE_TM_GMTOFF		/*-*/
#define HAVE_FCHOWN		/*-*/
#define HAVE_UTIMES		/*-*/
#define HAVE_UTIMENSAT
#define _INCOMPLETE_XOPEN_C063

			/* if your OS supports a BSD-style login.conf file */
/* #define LOGIN_CAP			*/

			/* if your OS supports BSD authentication */
/*#define BSD_AUTH			*/

			/* Define this to run crontab setgid instead of   
			 * setuid root.  Group access will be used to read
			 * the tabs/atjobs dirs and the allow/deny files.
			 * If this is not defined then crontab and at
			 * must be setuid root.
			 */
/*#define CRON_GROUP	"crontab"	*/

#define MAXTABSIZE_DEFAULT	(1024*256)
