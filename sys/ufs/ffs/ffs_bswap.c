/*	$NetBSD$	*/

/*
 * Copyright (c) 1998 Manuel Bouyer.
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
 *
 */

#if HAVE_NBTOOL_CONFIG_H
#include "nbtool_config.h"
#endif

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

#include <sys/param.h>
#if defined(_KERNEL)
#include <sys/systm.h>
#endif

#include <ufs/ufs/dinode.h>
#include <ufs/ufs/quota.h>
#include <ufs/ufs/ufs_bswap.h>
#include <ufs/ffs/fs.h>
#include <ufs/ffs/ffs_extern.h>

#if !defined(_KERNEL)
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define panic(x)	printf("%s\n", (x)), abort()
#endif

void
ffs_sb_swap(struct fs *o, struct fs *n)
{
	size_t i;
	u_int32_t *o32, *n32;

	/*
	 * In order to avoid a lot of lines, as the first N fields (52)
	 * of the superblock up to fs_fmod are u_int32_t, we just loop
	 * here to convert them.
	 */
	o32 = (u_int32_t *)o;
	n32 = (u_int32_t *)n;
	for (i = 0; i < offsetof(struct fs, fs_fmod) / sizeof(u_int32_t); i++)
		n32[i] = bswap32(o32[i]);

	n->fs_swuid = bswap64(o->fs_swuid);
	n->fs_cgrotor = bswap32(o->fs_cgrotor); /* Unused */
	n->fs_old_cpc = bswap32(o->fs_old_cpc);

	/* These fields overlap with a possible location for the
	 * historic FS_DYNAMICPOSTBLFMT postbl table, and with the
	 * first half of the historic FS_42POSTBLFMT postbl table.
	 */
	n->fs_maxbsize = bswap32(o->fs_maxbsize);
	/* XXX journal */
	n->fs_quota_magic = bswap32(o->fs_quota_magic);
	for (i = 0; i < MAXQUOTAS; i++)
		n->fs_quotafile[i] = bswap64(o->fs_quotafile[i]);
	n->fs_sblockloc = bswap64(o->fs_sblockloc);
	ffs_csumtotal_swap(&o->fs_cstotal, &n->fs_cstotal);
	n->fs_time = bswap64(o->fs_time);
	n->fs_size = bswap64(o->fs_size);
	n->fs_dsize = bswap64(o->fs_dsize);
	n->fs_csaddr = bswap64(o->fs_csaddr);
	n->fs_pendingblocks = bswap64(o->fs_pendingblocks);
	n->fs_pendinginodes = bswap32(o->fs_pendinginodes);

	/* These fields overlap with the second half of the
	 * historic FS_42POSTBLFMT postbl table
	 */
	for (i = 0; i < FSMAXSNAP; i++)
		n->fs_snapinum[i] = bswap32(o->fs_snapinum[i]);
	n->fs_avgfilesize = bswap32(o->fs_avgfilesize);
	n->fs_avgfpdir = bswap32(o->fs_avgfpdir);
	/* fs_sparecon[28] - ignore for now */
	n->fs_flags = bswap32(o->fs_flags);
	n->fs_contigsumsize = bswap32(o->fs_contigsumsize);
	n->fs_maxsymlinklen = bswap32(o->fs_maxsymlinklen);
	n->fs_old_inodefmt = bswap32(o->fs_old_inodefmt);
	n->fs_maxfilesize = bswap64(o->fs_maxfilesize);
	n->fs_qbmask = bswap64(o->fs_qbmask);
	n->fs_qfmask = bswap64(o->fs_qfmask);
	n->fs_state = bswap32(o->fs_state);
	n->fs_old_postblformat = bswap32(o->fs_old_postblformat);
	n->fs_old_nrpos = bswap32(o->fs_old_nrpos);
	n->fs_old_postbloff = bswap32(o->fs_old_postbloff);
	n->fs_old_rotbloff = bswap32(o->fs_old_rotbloff);

	n->fs_magic = bswap32(o->fs_magic);
}

void
ffs_dinode1_swap(struct ufs1_dinode *o, struct ufs1_dinode *n)
{

	n->di_mode = bswap16(o->di_mode);
	n->di_nlink = bswap16(o->di_nlink);
	n->di_oldids[0] = bswap16(o->di_oldids[0]);
	n->di_oldids[1] = bswap16(o->di_oldids[1]);
	n->di_size = bswap64(o->di_size);
	n->di_atime = bswap32(o->di_atime);
	n->di_atimensec = bswap32(o->di_atimensec);
	n->di_mtime = bswap32(o->di_mtime);
	n->di_mtimensec = bswap32(o->di_mtimensec);
	n->di_ctime = bswap32(o->di_ctime);
	n->di_ctimensec = bswap32(o->di_ctimensec);
	memcpy(n->di_db, o->di_db, (UFS_NDADDR + UFS_NIADDR) * sizeof(u_int32_t));
	n->di_flags = bswap32(o->di_flags);
	n->di_blocks = bswap32(o->di_blocks);
	n->di_gen = bswap32(o->di_gen);
	n->di_uid = bswap32(o->di_uid);
	n->di_gid = bswap32(o->di_gid);
}

void
ffs_dinode2_swap(struct ufs2_dinode *o, struct ufs2_dinode *n)
{
	n->di_mode = bswap16(o->di_mode);
	n->di_nlink = bswap16(o->di_nlink);
	n->di_uid = bswap32(o->di_uid);
	n->di_gid = bswap32(o->di_gid);
	n->di_blksize = bswap32(o->di_blksize);
	n->di_size = bswap64(o->di_size);
	n->di_blocks = bswap64(o->di_blocks);
	n->di_atime = bswap64(o->di_atime);
	n->di_atimensec = bswap32(o->di_atimensec);
	n->di_mtime = bswap64(o->di_mtime);
	n->di_mtimensec = bswap32(o->di_mtimensec);
	n->di_ctime = bswap64(o->di_ctime);
	n->di_ctimensec = bswap32(o->di_ctimensec);
	n->di_birthtime = bswap64(o->di_birthtime);
	n->di_birthnsec = bswap32(o->di_birthnsec);
	n->di_gen = bswap32(o->di_gen);
	n->di_kernflags = bswap32(o->di_kernflags);
	n->di_flags = bswap32(o->di_flags);
	n->di_extsize = bswap32(o->di_extsize);
	memcpy(n->di_extb, o->di_extb, (UFS_NXADDR + UFS_NDADDR + UFS_NIADDR) * 8);
}

void
ffs_csum_swap(struct csum *o, struct csum *n, int size)
{
	size_t i;
	u_int32_t *oint, *nint;

	oint = (u_int32_t*)o;
	nint = (u_int32_t*)n;

	for (i = 0; i < size / sizeof(u_int32_t); i++)
		nint[i] = bswap32(oint[i]);
}

void
ffs_csumtotal_swap(struct csum_total *o, struct csum_total *n)
{
	n->cs_ndir = bswap64(o->cs_ndir);
	n->cs_nbfree = bswap64(o->cs_nbfree);
	n->cs_nifree = bswap64(o->cs_nifree);
	n->cs_nffree = bswap64(o->cs_nffree);
}

/*
 * Note that ffs_cg_swap may be called with o == n.
 */
void
ffs_cg_swap(struct cg *o, struct cg *n, struct fs *fs)
{
	int i;
	u_int32_t *n32, *o32;
	u_int16_t *n16, *o16;
	int32_t btotoff, boff, clustersumoff;

	n->cg_firstfield = bswap32(o->cg_firstfield);
	n->cg_magic = bswap32(o->cg_magic);
	n->cg_old_time = bswap32(o->cg_old_time);
	n->cg_cgx = bswap32(o->cg_cgx);
	n->cg_old_ncyl = bswap16(o->cg_old_ncyl);
	n->cg_old_niblk = bswap16(o->cg_old_niblk);
	n->cg_ndblk = bswap32(o->cg_ndblk);
	n->cg_cs.cs_ndir = bswap32(o->cg_cs.cs_ndir);
	n->cg_cs.cs_nbfree = bswap32(o->cg_cs.cs_nbfree);
	n->cg_cs.cs_nifree = bswap32(o->cg_cs.cs_nifree);
	n->cg_cs.cs_nffree = bswap32(o->cg_cs.cs_nffree);
	n->cg_rotor = bswap32(o->cg_rotor);
	n->cg_frotor = bswap32(o->cg_frotor);
	n->cg_irotor = bswap32(o->cg_irotor);
	for (i = 0; i < MAXFRAG; i++)
		n->cg_frsum[i] = bswap32(o->cg_frsum[i]);

	if ((fs->fs_magic != FS_UFS2_MAGIC) &&
			(fs->fs_old_postblformat == FS_42POSTBLFMT)) { /* old format */
		struct ocg *on, *oo;
		int j;
		on = (struct ocg *)n;
		oo = (struct ocg *)o;

		for (i = 0; i < 32; i++) {
			on->cg_btot[i] = bswap32(oo->cg_btot[i]);
			for (j = 0; j < 8; j++)
				on->cg_b[i][j] = bswap16(oo->cg_b[i][j]);
		}
		memmove(on->cg_iused, oo->cg_iused, 256);
		on->cg_magic = bswap32(oo->cg_magic);
	} else {  /* new format */

		n->cg_old_btotoff = bswap32(o->cg_old_btotoff);
		n->cg_old_boff = bswap32(o->cg_old_boff);
		n->cg_iusedoff = bswap32(o->cg_iusedoff);
		n->cg_freeoff = bswap32(o->cg_freeoff);
		n->cg_nextfreeoff = bswap32(o->cg_nextfreeoff);
		n->cg_clustersumoff = bswap32(o->cg_clustersumoff);
		n->cg_clusteroff = bswap32(o->cg_clusteroff);
		n->cg_nclusterblks = bswap32(o->cg_nclusterblks);
		n->cg_niblk = bswap32(o->cg_niblk);
		n->cg_initediblk = bswap32(o->cg_initediblk);
		n->cg_time = bswap64(o->cg_time);

		if (n->cg_magic == CG_MAGIC) {
			btotoff = n->cg_old_btotoff;
			boff = n->cg_old_boff;
			clustersumoff = n->cg_clustersumoff;
		} else {
			btotoff = bswap32(n->cg_old_btotoff);
			boff = bswap32(n->cg_old_boff);
			clustersumoff = bswap32(n->cg_clustersumoff);
		}

		n32 = (u_int32_t *)((u_int8_t *)n + clustersumoff);
		o32 = (u_int32_t *)((u_int8_t *)o + clustersumoff);
		for (i = 1; i < fs->fs_contigsumsize + 1; i++)
			n32[i] = bswap32(o32[i]);

		if (fs->fs_magic == FS_UFS2_MAGIC)
			return;

		n32 = (u_int32_t *)((u_int8_t *)n + btotoff);
		o32 = (u_int32_t *)((u_int8_t *)o + btotoff);
		n16 = (u_int16_t *)((u_int8_t *)n + boff);
		o16 = (u_int16_t *)((u_int8_t *)o + boff);

		for (i = 0; i < fs->fs_old_cpg; i++)
			n32[i] = bswap32(o32[i]);

		for (i = 0; i < fs->fs_old_cpg * fs->fs_old_nrpos; i++)
			n16[i] = bswap16(o16[i]);
	}
}
