/*	$NetBSD$	*/
/*  from NetBSD: extattr.h,v 1.10 2011/10/09 21:15:34 chs Exp  */

/*-
 * Copyright (c) 1999-2001 Robert N. M. Watson
 * All rights reserved.
 *
 * This software was developed by Robert Watson for the TrustedBSD Project.
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
 * $FreeBSD: src/sys/ufs/ufs/extattr.h,v 1.20 2005/01/31 08:16:45 imp Exp $
 */

/*
 * Support for file system extended attributes on the ULFS1 file system.
 * Developed by the TrustedBSD Project.
 */

#ifndef _UFS_LFS_ULFS_EXTATTR_H_
#define	_UFS_LFS_ULFS_EXTATTR_H_

#define	ULFS_EXTATTR_MAGIC		0x00b5d5ec
#define	ULFS_EXTATTR_VERSION		0x00000003
#define	ULFS_EXTATTR_FSROOTSUBDIR	".attribute"
#define	ULFS_EXTATTR_SUBDIR_SYSTEM	"system"
#define	ULFS_EXTATTR_SUBDIR_USER		"user"
#define	ULFS_EXTATTR_MAXEXTATTRNAME	65	/* including null */

#define	ULFS_EXTATTR_ATTR_FLAG_INUSE	0x00000001	/* attr has been set */
#define	ULFS_EXTATTR_PERM_KERNEL		0x00000000
#define	ULFS_EXTATTR_PERM_ROOT		0x00000001
#define	ULFS_EXTATTR_PERM_OWNER		0x00000002
#define	ULFS_EXTATTR_PERM_ANYONE		0x00000003

#define	ULFS_EXTATTR_UEPM_INITIALIZED	0x00000001
#define	ULFS_EXTATTR_UEPM_STARTED	0x00000002

#define	ULFS_EXTATTR_CMD_START		EXTATTR_CMD_START
#define	ULFS_EXTATTR_CMD_STOP		EXTATTR_CMD_STOP
#define	ULFS_EXTATTR_CMD_ENABLE		0x00000003
#define	ULFS_EXTATTR_CMD_DISABLE		0x00000004

struct ulfs_extattr_fileheader {
	uint32_t	uef_magic;	/* magic number for sanity checking */
	uint32_t	uef_version;	/* version of attribute file */
	uint32_t	uef_size;	/* size of attributes, w/o header */
};

struct ulfs_extattr_header {
	uint32_t	ueh_flags;	/* flags for attribute */
	uint32_t	ueh_len;	/* local defined length; <= uef_size */
	uint32_t	ueh_i_gen;	/* generation number for sanity */
	/* data follows the header */
};

#ifdef _KERNEL

#ifdef MALLOC_DECLARE
MALLOC_DECLARE(M_EXTATTR);
#endif

struct vnode;
LIST_HEAD(ulfs_extattr_list_head, ulfs_extattr_list_entry);
struct ulfs_extattr_list_entry {
	LIST_ENTRY(ulfs_extattr_list_entry)	uele_entries;
	struct ulfs_extattr_fileheader		uele_fileheader;
	int		uele_attrnamespace;
	char		uele_attrname[ULFS_EXTATTR_MAXEXTATTRNAME];
	struct vnode	*uele_backing_vnode;
	int		uele_flags;
};

/* uele_flags */
#define	UELE_F_NEEDSWAP		0x01	/* needs byte swap */

#define	UELE_NEEDSWAP(uele)	((uele)->uele_flags & UELE_F_NEEDSWAP)

struct lock;
struct ulfs_extattr_per_mount {
	kmutex_t			uepm_lock;
	struct ulfs_extattr_list_head	uepm_list;
	kauth_cred_t			uepm_ucred;
	int				uepm_lockcnt;
	int				uepm_flags;
};

void	ulfs_extattr_uepm_init(struct ulfs_extattr_per_mount *uepm);
void	ulfs_extattr_uepm_destroy(struct ulfs_extattr_per_mount *uepm);
int	ulfs_extattr_start(struct mount *mp, struct lwp *l);
int	ulfs_extattr_autostart(struct mount *mp, struct lwp *l);
void	ulfs_extattr_stop(struct mount *mp, struct lwp *l);
int	ulfs_extattrctl(struct mount *mp, int cmd, struct vnode *filename,
	    int attrnamespace, const char *attrname);
struct vop_getextattr_args;
int	ulfs_getextattr(struct vop_getextattr_args *ap);
struct vop_deleteextattr_args;
int	ulfs_deleteextattr(struct vop_deleteextattr_args *ap);
struct vop_setextattr_args;
int	ulfs_setextattr(struct vop_setextattr_args *ap);
struct vop_listextattr_args;
int	ulfs_listextattr(struct vop_listextattr_args *ap);
void	ulfs_extattr_vnode_inactive(struct vnode *vp, struct lwp *l);

void	ulfs_extattr_init(void);
void	ulfs_extattr_done(void);

#endif /* !_KERNEL */

#endif /* !_UFS_LFS_ULFS_EXTATTR_H_ */
