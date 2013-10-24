/*	$NetBSD$	*/

#ifndef	_MACHINE_CDEFS_H_
#define	_MACHINE_CDEFS_H_

/* No arch-specific cdefs. */
#ifdef __arch64__
#define	__ALIGNBYTES		0xf
#else
#define	__ALIGNBYTES		0x7
#endif

#endif /* !_MACHINE_CDEFS_H_ */
