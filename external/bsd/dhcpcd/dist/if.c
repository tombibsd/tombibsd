#include <sys/cdefs.h>
 __RCSID("$NetBSD$");

/*
 * dhcpcd - DHCP client daemon
 * Copyright (c) 2006-2015 Roy Marples <roy@marples.name>
 * All rights reserved

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
 */

#include <sys/param.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <net/if.h>
#include <net/if_arp.h>
#include <netinet/in.h>
#ifdef __FreeBSD__ /* Needed so that including netinet6/in6_var.h works */
#  include <net/if_var.h>
#endif
#ifdef AF_LINK
#  include <net/if_dl.h>
#  include <net/if_types.h>
#  include <netinet/in_var.h>
#endif
#ifdef AF_PACKET
#  include <netpacket/packet.h>
#endif
#ifdef SIOCGIFMEDIA
#  include <net/if_media.h>
#endif
#include <net/route.h>

#include <ctype.h>
#include <errno.h>
#include <ifaddrs.h>
#include <fnmatch.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "common.h"
#include "dev.h"
#include "dhcp.h"
#include "dhcp6.h"
#include "if.h"
#include "if-options.h"
#include "ipv4.h"
#include "ipv6nd.h"

#ifdef __QNX__
/* QNX carries defines for, but does not actually support PF_LINK */
#undef IFLR_ACTIVE
#endif

void
if_free(struct interface *ifp)
{

	if (ifp == NULL)
		return;
	ipv4_free(ifp);
	dhcp_free(ifp);
	dhcp6_free(ifp);
	ipv6nd_free(ifp);
	ipv6_free(ifp);
	free_options(ifp->options);
	free(ifp);
}

int
if_carrier(struct interface *iface)
{
	int s, r;
	struct ifreq ifr;
#ifdef SIOCGIFMEDIA
	struct ifmediareq ifmr;
#endif

	if ((s = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
		return LINK_UNKNOWN;
	memset(&ifr, 0, sizeof(ifr));
	strlcpy(ifr.ifr_name, iface->name, sizeof(ifr.ifr_name));
	if (ioctl(s, SIOCGIFFLAGS, &ifr) == -1) {
		close(s);
		return LINK_UNKNOWN;
	}
	iface->flags = (unsigned int)ifr.ifr_flags;

#ifdef SIOCGIFMEDIA
	memset(&ifmr, 0, sizeof(ifmr));
	strlcpy(ifmr.ifm_name, iface->name, sizeof(ifmr.ifm_name));
	if (ioctl(s, SIOCGIFMEDIA, &ifmr) != -1 &&
	    ifmr.ifm_status & IFM_AVALID)
		r = (ifmr.ifm_status & IFM_ACTIVE) ? LINK_UP : LINK_DOWN;
	else
		r = ifr.ifr_flags & IFF_RUNNING ? LINK_UP : LINK_UNKNOWN;
#else
	r = ifr.ifr_flags & IFF_RUNNING ? LINK_UP : LINK_DOWN;
#endif
	close(s);
	return r;
}

int
if_setflag(struct interface *ifp, short flag)
{
	struct ifreq ifr;
	int s, r;

	if ((s = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
		return -1;
	memset(&ifr, 0, sizeof(ifr));
	strlcpy(ifr.ifr_name, ifp->name, sizeof(ifr.ifr_name));
	r = -1;
	if (ioctl(s, SIOCGIFFLAGS, &ifr) == 0) {
		if (flag == 0 || (ifr.ifr_flags & flag) == flag)
			r = 0;
		else {
			ifr.ifr_flags |= flag;
			if (ioctl(s, SIOCSIFFLAGS, &ifr) == 0)
				r = 0;
		}
		ifp->flags = (unsigned int)ifr.ifr_flags;
	}
	close(s);
	return r;
}

static int
if_hasconf(struct dhcpcd_ctx *ctx, const char *ifname)
{
	int i;

	for (i = 0; i < ctx->ifcc; i++) {
		if (strcmp(ctx->ifcv[i], ifname) == 0)
			return 1;
	}
	return 0;
}

struct if_head *
if_discover(struct dhcpcd_ctx *ctx, int argc, char * const *argv)
{
	struct ifaddrs *ifaddrs, *ifa;
	char *p;
	int i;
	struct if_head *ifs;
	struct interface *ifp;
#ifdef __linux__
	char ifn[IF_NAMESIZE];
#endif
#ifdef INET
	const struct sockaddr_in *addr;
	const struct sockaddr_in *net;
	const struct sockaddr_in *dst;
#endif
#ifdef INET6
	struct sockaddr_in6 *sin6, *net6;
	int ifa_flags;
#endif
#ifdef AF_LINK
	const struct sockaddr_dl *sdl;
#ifdef SIOCGIFPRIORITY
	struct ifreq ifr;
	int s_inet;
#endif
#ifdef IFLR_ACTIVE
	struct if_laddrreq iflr;
	int s_link;
#endif

#ifdef SIOCGIFPRIORITY
	if ((s_inet = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
		return NULL;
#endif
#ifdef IFLR_ACTIVE
	if ((s_link = socket(PF_LINK, SOCK_DGRAM, 0)) == -1) {
#ifdef SIOCGIFPRIORITY
		close(s_inet);
#endif
		return NULL;
	}
	memset(&iflr, 0, sizeof(iflr));
#endif
#elif AF_PACKET
	const struct sockaddr_ll *sll;
#endif

	if (getifaddrs(&ifaddrs) == -1)
		return NULL;
	ifs = malloc(sizeof(*ifs));
	if (ifs == NULL)
		return NULL;
	TAILQ_INIT(ifs);

	for (ifa = ifaddrs; ifa; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr != NULL) {
#ifdef AF_LINK
			if (ifa->ifa_addr->sa_family != AF_LINK)
				continue;
#elif AF_PACKET
			if (ifa->ifa_addr->sa_family != AF_PACKET)
				continue;
#endif
		}

		/* It's possible for an interface to have >1 AF_LINK.
		 * For our purposes, we use the first one. */
		TAILQ_FOREACH(ifp, ifs, next) {
			if (strcmp(ifp->name, ifa->ifa_name) == 0)
				break;
		}
		if (ifp)
			continue;

		if (argc > 0) {
			for (i = 0; i < argc; i++) {
#ifdef __linux__
				/* Check the real interface name */
				strlcpy(ifn, argv[i], sizeof(ifn));
				p = strchr(ifn, ':');
				if (p)
					*p = '\0';
				if (strcmp(ifn, ifa->ifa_name) == 0)
					break;
#else
				if (strcmp(argv[i], ifa->ifa_name) == 0)
					break;
#endif
			}
			if (i == argc)
				continue;
			p = argv[i];
		} else {
			p = ifa->ifa_name;
#ifdef __linux__
			strlcpy(ifn, ifa->ifa_name, sizeof(ifn));
#endif
			/* -1 means we're discovering against a specific
			 * interface, but we still need the below rules
			 * to apply. */
			if (argc == -1 && strcmp(argv[0], ifa->ifa_name) != 0)
				continue;
		}
		for (i = 0; i < ctx->ifdc; i++)
			if (!fnmatch(ctx->ifdv[i], p, 0))
				break;
		if (i < ctx->ifdc)
			continue;
		for (i = 0; i < ctx->ifac; i++)
			if (!fnmatch(ctx->ifav[i], p, 0))
				break;
		if (ctx->ifac && i == ctx->ifac)
			continue;

		/* Ensure that the interface name has settled */
		if (!dev_initialized(ctx, p))
			continue;

		/* Don't allow loopback or pointopoint unless explicit */
		if (ifa->ifa_flags & (IFF_LOOPBACK | IFF_POINTOPOINT)) {
			if ((argc == 0 || argc == -1) &&
			    ctx->ifac == 0 && !if_hasconf(ctx, p))
				continue;
		}

		if (if_vimaster(p) == 1) {
			logger(ctx, argc ? LOG_ERR : LOG_DEBUG,
			    "%s: is a Virtual Interface Master, skipping", p);
			continue;
		}

		ifp = calloc(1, sizeof(*ifp));
		if (ifp == NULL) {
			logger(ctx, LOG_ERR, "%s: %m", __func__);
			break;
		}
		ifp->ctx = ctx;
#ifdef __linux__
		strlcpy(ifp->name, ifn, sizeof(ifp->name));
		strlcpy(ifp->alias, p, sizeof(ifp->alias));
#else
		strlcpy(ifp->name, p, sizeof(ifp->name));
#endif
		ifp->flags = ifa->ifa_flags;
		ifp->carrier = if_carrier(ifp);

		if (ifa->ifa_addr != NULL) {
#ifdef AF_LINK
			sdl = (const struct sockaddr_dl *)(void *)ifa->ifa_addr;

#ifdef IFLR_ACTIVE
			/* We need to check for active address */
			strlcpy(iflr.iflr_name, ifp->name,
			    sizeof(iflr.iflr_name));
			memcpy(&iflr.addr, ifa->ifa_addr,
			    MIN(ifa->ifa_addr->sa_len, sizeof(iflr.addr)));
			iflr.flags = IFLR_PREFIX;
			iflr.prefixlen = (unsigned int)sdl->sdl_alen * NBBY;
			if (ioctl(s_link, SIOCGLIFADDR, &iflr) == -1 ||
			    !(iflr.flags & IFLR_ACTIVE))
			{
				if_free(ifp);
				continue;
			}
#endif

			ifp->index = sdl->sdl_index;
			switch(sdl->sdl_type) {
#ifdef IFT_BRIDGE
			case IFT_BRIDGE: /* FALLTHROUGH */
#endif
#ifdef IFT_PPP
			case IFT_PPP: /* FALLTHROUGH */
#endif
#ifdef IFT_PROPVIRTUAL
			case IFT_PROPVIRTUAL: /* FALLTHROUGH */
#endif
#if defined(IFT_BRIDGE) || defined(IFT_PPP) || defined(IFT_PROPVIRTUAL)
				/* Don't allow unless explicit */
				if ((argc == 0 || argc == -1) &&
				    ctx->ifac == 0 &&
				    !if_hasconf(ctx, ifp->name))
				{
					logger(ifp->ctx, LOG_DEBUG,
					    "%s: ignoring due to"
					    " interface type and"
					    " no config",
					    ifp->name);
					if_free(ifp);
					continue;
				}
				/* FALLTHROUGH */
#endif
#ifdef IFT_L2VLAN
			case IFT_L2VLAN: /* FALLTHROUGH */
#endif
#ifdef IFT_L3IPVLAN
			case IFT_L3IPVLAN: /* FALLTHROUGH */
#endif
			case IFT_ETHER:
				ifp->family = ARPHRD_ETHER;
				break;
#ifdef IFT_IEEE1394
			case IFT_IEEE1394:
				ifp->family = ARPHRD_IEEE1394;
				break;
#endif
#ifdef IFT_INFINIBAND
			case IFT_INFINIBAND:
				ifp->family = ARPHRD_INFINIBAND;
				break;
#endif
			default:
				/* Don't allow unless explicit */
				if ((argc == 0 || argc == -1) &&
				    ctx->ifac == 0 &&
				    !if_hasconf(ctx, ifp->name))
				{
					if_free(ifp);
					continue;
				}
				logger(ifp->ctx, LOG_WARNING,
				    "%s: unsupported interface type %.2x",
				    ifp->name, sdl->sdl_type);
				/* Pretend it's ethernet */
				ifp->family = ARPHRD_ETHER;
				break;
			}
			ifp->hwlen = sdl->sdl_alen;
#ifndef CLLADDR
#  define CLLADDR(s) ((const char *)((s)->sdl_data + (s)->sdl_nlen))
#endif
			memcpy(ifp->hwaddr, CLLADDR(sdl), ifp->hwlen);
#elif AF_PACKET
			sll = (const struct sockaddr_ll *)(void *)ifa->ifa_addr;
			ifp->index = (unsigned int)sll->sll_ifindex;
			ifp->family = sll->sll_hatype;
			ifp->hwlen = sll->sll_halen;
			if (ifp->hwlen != 0)
				memcpy(ifp->hwaddr, sll->sll_addr, ifp->hwlen);
#endif
		}
#ifdef __linux__
		/* PPP addresses on Linux don't have hardware addresses */
		else
			ifp->index = if_nametoindex(ifp->name);
#endif

		/* We only work on ethernet by default */
		if (ifp->family != ARPHRD_ETHER) {
			if ((argc == 0 || argc == -1) &&
			    ctx->ifac == 0 && !if_hasconf(ctx, ifp->name))
			{
				if_free(ifp);
				continue;
			}
			switch (ifp->family) {
			case ARPHRD_IEEE1394:
			case ARPHRD_INFINIBAND:
#ifdef ARPHRD_LOOPBACK
			case ARPHRD_LOOPBACK:
#endif
#ifdef ARPHRD_PPP
			case ARPHRD_PPP:
#endif
				/* We don't warn for supported families */
				break;

/* IFT already checked */
#ifndef AF_LINK
			default:
				logger(ifp->ctx, LOG_WARNING,
				    "%s: unsupported interface family %.2x",
				    ifp->name, ifp->family);
				break;
#endif
			}
		}

		/* Handle any platform init for the interface */
		if (if_init(ifp) == -1) {
			logger(ifp->ctx, LOG_ERR, "%s: if_init: %m", p);
			if_free(ifp);
			continue;
		}

		/* Ensure that the MTU is big enough for DHCP */
		if (if_getmtu(ifp->name) < MTU_MIN &&
		    if_setmtu(ifp->name, MTU_MIN) == -1)
		{
			logger(ifp->ctx, LOG_ERR, "%s: set_mtu: %m", p);
			if_free(ifp);
			continue;
		}

#ifdef SIOCGIFPRIORITY
		/* Respect the interface priority */
		memset(&ifr, 0, sizeof(ifr));
		strlcpy(ifr.ifr_name, ifp->name, sizeof(ifr.ifr_name));
		if (ioctl(s_inet, SIOCGIFPRIORITY, &ifr) == 0)
			ifp->metric = ifr.ifr_metric;
#else
		/* We reserve the 100 range for virtual interfaces, if and when
		 * we can work them out. */
		ifp->metric = 200 + ifp->index;
		if (if_getssid(ifp) != -1) {
			ifp->wireless = 1;
			ifp->metric += 100;
		}
#endif

		TAILQ_INSERT_TAIL(ifs, ifp, next);
	}

	for (ifa = ifaddrs; ifa; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL)
			continue;
		switch(ifa->ifa_addr->sa_family) {
#ifdef INET
		case AF_INET:
			addr = (const struct sockaddr_in *)
			    (void *)ifa->ifa_addr;
			net = (const struct sockaddr_in *)
			    (void *)ifa->ifa_netmask;
			if (ifa->ifa_flags & IFF_POINTOPOINT)
				dst = (const struct sockaddr_in *)
				    (void *)ifa->ifa_dstaddr;
			else
				dst = NULL;
			ipv4_handleifa(ctx, RTM_NEWADDR, ifs, ifa->ifa_name,
				&addr->sin_addr,
				&net->sin_addr,
				dst ? &dst->sin_addr : NULL);
			break;
#endif
#ifdef INET6
		case AF_INET6:
			TAILQ_FOREACH(ifp, ifs, next) {
				if (strcmp(ifp->name, ifa->ifa_name) == 0)
					break;
			}
			if (ifp == NULL)
				break; /* Should be impossible */
			sin6 = (struct sockaddr_in6 *)(void *)ifa->ifa_addr;
			net6 = (struct sockaddr_in6 *)(void *)ifa->ifa_netmask;
#ifdef __KAME__
			if (IN6_IS_ADDR_LINKLOCAL(&sin6->sin6_addr))
				/* Remove the scope from the address */
				sin6->sin6_addr.s6_addr[2] =
				    sin6->sin6_addr.s6_addr[3] = '\0';
#endif
			ifa_flags = if_addrflags6(&sin6->sin6_addr, ifp);
			if (ifa_flags != -1)
				ipv6_handleifa(ctx, RTM_NEWADDR, ifs,
				    ifa->ifa_name,
				    &sin6->sin6_addr,
				    ipv6_prefixlen(&net6->sin6_addr),
				    ifa_flags);
			break;
#endif
		}
	}

	freeifaddrs(ifaddrs);

#ifdef SIOCGIFPRIORITY
	close(s_inet);
#endif
#ifdef IFLR_ACTIVE
	close(s_link);
#endif

	return ifs;
}

static struct interface *
if_findindexname(struct dhcpcd_ctx *ctx, unsigned int idx, const char *name)
{
	struct interface *ifp;

	if (ctx != NULL && ctx->ifaces != NULL) {
		TAILQ_FOREACH(ifp, ctx->ifaces, next) {
			if ((ifp->options == NULL ||
			    !(ifp->options->options & DHCPCD_PFXDLGONLY)) &&
			    ((name && strcmp(ifp->name, name) == 0) ||
#ifdef __linux__
			    (name && strcmp(ifp->alias, name) == 0) ||
#endif
			    (!name && ifp->index == idx)))
				return ifp;
		}
	}
	return NULL;
}

struct interface *
if_find(struct dhcpcd_ctx *ctx, const char *name)
{

	return if_findindexname(ctx, 0, name);
}

struct interface *
if_findindex(struct dhcpcd_ctx *ctx, unsigned int idx)
{

	return if_findindexname(ctx, idx, NULL);
}

int
if_domtu(const char *ifname, short int mtu)
{
	int s, r;
	struct ifreq ifr;

	if ((s = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
		return -1;
	memset(&ifr, 0, sizeof(ifr));
	strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
	ifr.ifr_mtu = mtu;
	r = ioctl(s, mtu ? SIOCSIFMTU : SIOCGIFMTU, &ifr);
	close(s);
	if (r == -1)
		return -1;
	return ifr.ifr_mtu;
}

/* Interface comparer for working out ordering. */
static int
if_cmp(const struct interface *si, const struct interface *ti)
{
#ifdef INET
	int r;
#endif

	/* Always prefer master interfaces */
	if (!(si->options->options & DHCPCD_PFXDLGONLY) &&
	    ti->options->options & DHCPCD_PFXDLGONLY)
		return -1;
	if (si->options->options & DHCPCD_PFXDLGONLY &&
	    !(ti->options->options & DHCPCD_PFXDLGONLY))
		return 1;

	if (D_STATE_RUNNING(si) && !D_STATE_RUNNING(ti))
		return -1;
	if (!D_STATE_RUNNING(si) && D_STATE_RUNNING(ti))
		return 1;
	if (RS_STATE_RUNNING(si) && !RS_STATE_RUNNING(ti))
		return -1;
	if (!RS_STATE_RUNNING(si) && RS_STATE_RUNNING(ti))
		return 1;
	if (D6_STATE_RUNNING(si) && !D6_STATE_RUNNING(ti))
		return -1;
	if (!D6_STATE_RUNNING(si) && D6_STATE_RUNNING(ti))
		return 1;

#ifdef INET
	/* Special attention needed hereto due take states and IPv4LL. */
	if ((r = ipv4_ifcmp(si, ti)) != 0)
		return r;
#endif

	/* Then carrier status. */
	if (si->carrier > ti->carrier)
		return -1;
	if (si->carrier < ti->carrier)
		return 1;
	/* Finally, metric */
	if (si->metric < ti->metric)
		return -1;
	if (si->metric > ti->metric)
		return 1;
	return 0;
}

/* Sort the interfaces into a preferred order - best first, worst last. */
void
if_sortinterfaces(struct dhcpcd_ctx *ctx)
{
	struct if_head sorted;
	struct interface *ifp, *ift;

	if (ctx->ifaces == NULL ||
	    (ifp = TAILQ_FIRST(ctx->ifaces)) == NULL ||
	    TAILQ_NEXT(ifp, next) == NULL)
		return;

	TAILQ_INIT(&sorted);
	TAILQ_REMOVE(ctx->ifaces, ifp, next);
	TAILQ_INSERT_HEAD(&sorted, ifp, next);
	while ((ifp = TAILQ_FIRST(ctx->ifaces))) {
		TAILQ_REMOVE(ctx->ifaces, ifp, next);
		TAILQ_FOREACH(ift, &sorted, next) {
			if (if_cmp(ifp, ift) == -1) {
				TAILQ_INSERT_BEFORE(ift, ifp, next);
				break;
			}
		}
		if (ift == NULL)
			TAILQ_INSERT_TAIL(&sorted, ifp, next);
	}
	TAILQ_CONCAT(ctx->ifaces, &sorted, next);
}
