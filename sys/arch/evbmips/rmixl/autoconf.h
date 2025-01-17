/*	$NetBSD$	*/

#ifndef _EVBMIPS_RMIXL_AUTOCONF_H_
#define _EVBMIPS_RMIXL_AUTOCONF_H_

struct mainbus_softc {
	device_t	sc_dev;
	int		sc_node_next;
	uint64_t	sc_node_mask;
};

struct mainbus_attach_args {
	const char     *ma_name;
	int		ma_node;
};

#endif	/* _EVBMIPS_RMIXL_AUTOCONF_H_ */
