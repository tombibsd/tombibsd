/*	$NetBSD$	*/

uint16_t	dkcksum(const struct disklabel *);
uint16_t	dkcksum_sized(const struct disklabel *, size_t);
