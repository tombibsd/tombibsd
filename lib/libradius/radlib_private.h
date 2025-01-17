/* $NetBSD$ */

/*-
 * Copyright 1998 Juniper Networks, Inc.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	$FreeBSD: /repoman/r/ncvs/src/lib/libradius/radlib_private.h,v 1.6 2004/04/27 15:00:29 ru Exp $
 */

#ifndef RADLIB_PRIVATE_H
#define RADLIB_PRIVATE_H

#include <sys/types.h>
#include <netinet/in.h>

#include "radlib.h"
#include "radlib_vs.h"

/* Handle types */
#define RADIUS_AUTH		0   /* RADIUS authentication, default */
#define RADIUS_ACCT		1   /* RADIUS accounting */

/* Defaults */
#define MAXTRIES		3
#define PATH_RADIUS_CONF	"/etc/radius.conf"
#define RADIUS_PORT		1812
#define RADACCT_PORT		1813
#define TIMEOUT			3	/* In seconds */

/* Limits */
#define ERRSIZE		128		/* Maximum error message length */
#define MAXCONFLINE	1024		/* Maximum config file line length */
#define MAXSERVERS	10		/* Maximum number of servers to try */
#define MSGSIZE		4096		/* Maximum RADIUS message */
#define PASSSIZE	128		/* Maximum significant password chars */

/* Positions of fields in RADIUS messages */
#define POS_CODE	0		/* Message code */
#define POS_IDENT	1		/* Identifier */
#define POS_LENGTH	2		/* Message length */
#define POS_AUTH	4		/* Authenticator */
#define LEN_AUTH	16		/* Length of authenticator */
#define POS_ATTRS	20		/* Start of attributes */

struct rad_server {
	struct sockaddr_in addr;	/* Address of server */
	char		*secret;	/* Shared secret */
	int		 timeout;	/* Timeout in seconds */
	int		 max_tries;	/* Number of tries before giving up */
	int		 num_tries;	/* Number of tries so far */
};

struct rad_handle {
	int		 fd;		/* Socket file descriptor */
	struct rad_server servers[MAXSERVERS];	/* Servers to contact */
	size_t		 num_servers;	/* Number of valid server entries */
	int		 ident;		/* Current identifier value */
	char		 errmsg[ERRSIZE];	/* Most recent error message */
	unsigned char	 request[MSGSIZE];	/* Request to send */
	char	 	 request_created; /* rad_create_request() called? */
	size_t		 req_len;	/* Length of request */
	char		 pass[PASSSIZE];	/* Cleartext password */
	size_t		 pass_len;	/* Length of cleartext password */
	size_t		 pass_pos;	/* Position of scrambled password */
	char	 	 chap_pass;	/* Have we got a CHAP_PASSWORD ? */
	size_t		 authentic_pos;	/* Position of message authenticator */
	char		 eap_msg;	/* Are we an EAP Proxy? */
	unsigned char	 response[MSGSIZE];	/* Response received */
	size_t		 resp_len;	/* Length of response */
	size_t		 resp_pos;	/* Current position scanning attrs */
	size_t		 total_tries;	/* How many requests we'll send */
	size_t		 try;		/* How many requests we've sent */
	size_t		 srv;		/* Server number we did last */
	int		 type;		/* Handle type */
};

struct vendor_attribute {
	u_int32_t vendor_value;
	u_char attrib_type;
	u_char attrib_len;
	u_char attrib_data[1];
};

#endif
