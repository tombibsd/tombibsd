/*	$NetBSD$	*/

/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
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
 * from: Utah $Hdr: grfvar.h 1.9 91/01/21$
 *
 *	@(#)grfvar.h	7.3 (Berkeley) 5/7/91
 */

/*
 * Structure passed as 'aux' during autoconf.
 */
typedef struct {
	cfprint_t	busprint;	/* grfbusprint function		*/
	int		from_bus_match;	/* called from grfbusmatch()	*/
	int		unit;		/* grf-unit we want to attach	*/
} grf_auxp_t;

struct ite_softc;

/* 
 * this struct is owned by the driver (grfcc)
 * and is passed to grf when grf is configed. The ite also 
 * uses it... 
 */
struct	grf_softc {
	device_t	g_device;	/* config sets this up.		*/
	struct grfinfo	g_display;	/* hardware descr. (for ioctl)	*/
	int		g_flags;	/* software flags		*/
	int		g_unit;		/* grf unit we want/have	*/
	dev_t		g_itedev;	/* ite device number		*/
	dev_t		g_grfdev;	/* grf device number		*/
	dev_t		g_viewdev;	/* view device number		*/
	void *		g_data;		/* device dependent data	*/
	int		(*g_mode)(struct grf_softc *, int, void *,
								int, int);
	int		g_conpri;	/* priority of ite as console	*/
	void		(*g_iteinit)(struct ite_softc *);
	void		(*g_itedeinit)(struct ite_softc *);
	void		(*g_iteclear)(struct ite_softc *, int, int,
								int, int);
	void		(*g_iteputc)(struct ite_softc *, int, int,
								int, int);
	void		(*g_itecursor)(struct ite_softc *, int);
	void		(*g_itescroll)(struct ite_softc *, int, int,
								int, int);
};

/* flags */
#define	GF_ALIVE	0x01
#define GF_OPEN		0x02
#define GF_EXCLUDE	0x04
#define GF_WANTED	0x08
#define GF_GRFON	0x10

/* software ids defined in grfioctl.h */

/* requests to mode routine (g_mode())*/
#define GM_GRFON		1
#define GM_GRFOFF		2
#define GM_GRFOVON		3
#define GM_GRFOVOFF		4
#define GM_GRFCONFIG		5
#define GM_GRFGETVMODE		6
#define GM_GRFSETVMODE		7
#define GM_GRFGETNUMVM		8
#define GM_GRFGETBANK		9
#define GM_GRFSETBANK		10
#define GM_GRFGETCURBANK	11
#define GM_GRFIOCTL		12

/* minor device interpretation */
#define GRFOVDEV	0x10	/* XXX no driver uses yet, overlay planes */
#define GRFIMDEV	0x20	/* XXX no driver uses yet, images planes  */
#define GRFUNIT(d)	((d) & 0x7)

#ifdef _KERNEL

int  grf_mode(struct grf_softc *, int, void *, int, int);
void grf_viewsync(struct grf_softc *);

extern struct grf_softc *grfsp[]; /* XXX */
#endif /* _KERNEL */
