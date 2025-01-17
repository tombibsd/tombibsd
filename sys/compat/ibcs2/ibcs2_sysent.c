/* $NetBSD$ */

/*
 * System call switch table.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from	NetBSD: syscalls.master,v 1.41 2013/11/07 19:37:18 njoly Exp
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

#if defined(_KERNEL_OPT)
#include "opt_sysv.h"
#endif
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/signal.h>
#include <sys/mount.h>
#include <sys/sched.h>
#include <sys/syscallargs.h>
#include <compat/sys/time.h>
#include <compat/ibcs2/ibcs2_types.h>
#include <compat/ibcs2/ibcs2_signal.h>
#include <compat/ibcs2/ibcs2_syscallargs.h>
#include <compat/ibcs2/ibcs2_statfs.h>

#define	s(type)	sizeof(type)
#define	n(type)	(sizeof(type)/sizeof (register_t))
#define	ns(type)	n(type), s(type)

struct sysent ibcs2_sysent[] = {
	{ 0, 0, 0,
	    (sy_call_t *)sys_nosys, 0, 0 },		/* 0 = syscall */
	{ ns(struct sys_exit_args), 0,
	    (sy_call_t *)sys_exit, 0, 0 },		/* 1 = exit */
	{ 0, 0, 0,
	    (sy_call_t *)sys_fork, 0, 0 },		/* 2 = fork */
	{ ns(struct ibcs2_sys_read_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_read, 0, 0 },	/* 3 = read */
	{ ns(struct sys_write_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_write, 0, 0 },		/* 4 = write */
	{ ns(struct ibcs2_sys_open_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_open, 0, 0 },	/* 5 = open */
	{ ns(struct sys_close_args), 0,
	    (sy_call_t *)sys_close, 0, 0 },		/* 6 = close */
	{ ns(struct ibcs2_sys_waitsys_args), 0,
	    (sy_call_t *)ibcs2_sys_waitsys, 0, 0 },	/* 7 = waitsys */
	{ ns(struct ibcs2_sys_creat_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_creat, 0, 0 },	/* 8 = creat */
	{ ns(struct sys_link_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_link, 0, 0 },		/* 9 = link */
	{ ns(struct sys_unlink_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_unlink, 0, 0 },		/* 10 = unlink */
	{ ns(struct ibcs2_sys_execv_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_execv, 0, 0 },	/* 11 = execv */
	{ ns(struct sys_chdir_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_chdir, 0, 0 },		/* 12 = chdir */
	{ ns(struct ibcs2_sys_time_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_time, 0, 0 },	/* 13 = time */
	{ ns(struct ibcs2_sys_mknod_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_mknod, 0, 0 },	/* 14 = mknod */
	{ ns(struct sys_chmod_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_chmod, 0, 0 },		/* 15 = chmod */
	{ ns(struct sys___posix_chown_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys___posix_chown, 0, 0 },	/* 16 = __posix_chown */
	{ ns(struct sys_obreak_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_obreak, 0, 0 },		/* 17 = obreak */
	{ ns(struct ibcs2_sys_stat_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_stat, 0, 0 },	/* 18 = stat */
	{ ns(struct compat_43_sys_lseek_args), 0,
	    (sy_call_t *)compat_43_sys_lseek, 0, 0 },	/* 19 = lseek */
	{ 0, 0, 0,
	    (sy_call_t *)sys_getpid_with_ppid, 0, 0 },/* 20 = getpid_with_ppid */
	{ ns(struct ibcs2_sys_mount_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_mount, 0, 0 },	/* 21 = mount */
	{ ns(struct ibcs2_sys_umount_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_umount, 0, 0 },	/* 22 = umount */
	{ ns(struct ibcs2_sys_setuid_args), 0,
	    (sy_call_t *)ibcs2_sys_setuid, 0, 0 },	/* 23 = setuid */
	{ 0, 0, 0,
	    (sy_call_t *)sys_getuid_with_euid, 0, 0 },/* 24 = getuid_with_euid */
	{ ns(struct ibcs2_sys_stime_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_stime, 0, 0 },	/* 25 = stime */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 26 = unimplemented ibcs2_ptrace */
	{ ns(struct ibcs2_sys_alarm_args), 0,
	    (sy_call_t *)ibcs2_sys_alarm, 0, 0 },	/* 27 = alarm */
	{ ns(struct ibcs2_sys_fstat_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_fstat, 0, 0 },	/* 28 = fstat */
	{ 0, 0, 0,
	    (sy_call_t *)ibcs2_sys_pause, 0, 0 },	/* 29 = pause */
	{ ns(struct ibcs2_sys_utime_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_utime, 0, 0 },	/* 30 = utime */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 31 = unimplemented was stty */
	{ ns(struct ibcs2_sys_gtty_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_gtty, 0, 0 },	/* 32 = gtty */
	{ ns(struct ibcs2_sys_access_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_access, 0, 0 },	/* 33 = access */
	{ ns(struct ibcs2_sys_nice_args), 0,
	    (sy_call_t *)ibcs2_sys_nice, 0, 0 },	/* 34 = nice */
	{ ns(struct ibcs2_sys_statfs_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_statfs, 0, 0 },	/* 35 = statfs */
	{ 0, 0, 0,
	    (sy_call_t *)sys_sync, 0, 0 },		/* 36 = sync */
	{ ns(struct ibcs2_sys_kill_args), 0,
	    (sy_call_t *)ibcs2_sys_kill, 0, 0 },	/* 37 = kill */
	{ ns(struct ibcs2_sys_fstatfs_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_fstatfs, 0, 0 },	/* 38 = fstatfs */
	{ ns(struct ibcs2_sys_pgrpsys_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_pgrpsys, 0, 0 },	/* 39 = pgrpsys */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 40 = unimplemented ibcs2_xenix */
	{ ns(struct sys_dup_args), 0,
	    (sy_call_t *)sys_dup, 0, 0 },		/* 41 = dup */
	{ 0, 0, 0,
	    (sy_call_t *)sys_pipe, 0, 0 },		/* 42 = pipe */
	{ ns(struct ibcs2_sys_times_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_times, 0, 0 },	/* 43 = times */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 44 = unimplemented profil */
	{ ns(struct ibcs2_sys_plock_args), 0,
	    (sy_call_t *)ibcs2_sys_plock, 0, 0 },	/* 45 = plock */
	{ ns(struct ibcs2_sys_setgid_args), 0,
	    (sy_call_t *)ibcs2_sys_setgid, 0, 0 },	/* 46 = setgid */
	{ 0, 0, 0,
	    (sy_call_t *)sys_getgid_with_egid, 0, 0 },/* 47 = getgid_with_egid */
	{ ns(struct ibcs2_sys_sigsys_args), 0,
	    (sy_call_t *)ibcs2_sys_sigsys, 0, 0 },	/* 48 = sigsys */
#ifdef SYSVMSG
	{ ns(struct ibcs2_sys_msgsys_args), 0,
	    (sy_call_t *)ibcs2_sys_msgsys, 0, 0 },	/* 49 = msgsys */
#else
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 49 = unimplemented msgsys */
#endif
	{ ns(struct ibcs2_sys_sysmachine_args), 0,
	    (sy_call_t *)ibcs2_sys_sysmachine, 0, 0 },/* 50 = sysmachine */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 51 = unimplemented ibcs2_acct */
#ifdef SYSVSHM
	{ ns(struct ibcs2_sys_shmsys_args), 0,
	    (sy_call_t *)ibcs2_sys_shmsys, 0, 0 },	/* 52 = shmsys */
#else
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 52 = unimplemented shmsys */
#endif
#ifdef SYSVSEM
	{ ns(struct ibcs2_sys_semsys_args), 0,
	    (sy_call_t *)ibcs2_sys_semsys, 0, 0 },	/* 53 = semsys */
#else
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 53 = unimplemented semsys */
#endif
	{ ns(struct ibcs2_sys_ioctl_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_ioctl, 0, 0 },	/* 54 = ioctl */
	{ ns(struct ibcs2_sys_uadmin_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_uadmin, 0, 0 },	/* 55 = uadmin */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 56 = unimplemented */
	{ ns(struct ibcs2_sys_utssys_args), 0,
	    (sy_call_t *)ibcs2_sys_utssys, 0, 0 },	/* 57 = utssys */
	{ ns(struct sys_fsync_args), 0,
	    (sy_call_t *)sys_fsync, 0, 0 },		/* 58 = fsync */
	{ ns(struct ibcs2_sys_execve_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_execve, 0, 0 },	/* 59 = execve */
	{ ns(struct sys_umask_args), 0,
	    (sy_call_t *)sys_umask, 0, 0 },		/* 60 = umask */
	{ ns(struct sys_chroot_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_chroot, 0, 0 },		/* 61 = chroot */
	{ ns(struct ibcs2_sys_fcntl_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_fcntl, 0, 0 },	/* 62 = fcntl */
	{ ns(struct ibcs2_sys_ulimit_args), 0,
	    (sy_call_t *)ibcs2_sys_ulimit, 0, 0 },	/* 63 = ulimit */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 64 = unimplemented reserved for unix/pc */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 65 = unimplemented reserved for unix/pc */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 66 = unimplemented reserved for unix/pc */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 67 = unimplemented reserved for unix/pc */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 68 = unimplemented reserved for unix/pc */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 69 = unimplemented reserved for unix/pc */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 70 = obsolete rfs_advfs */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 71 = obsolete rfs_unadvfs */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 72 = obsolete rfs_rmount */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 73 = obsolete rfs_rumount */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 74 = obsolete rfs_rfstart */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 75 = obsolete rfs_sigret */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 76 = obsolete rfs_rdebug */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 77 = obsolete rfs_rfstop */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 78 = unimplemented rfs_rfsys */
	{ ns(struct sys_rmdir_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_rmdir, 0, 0 },		/* 79 = rmdir */
	{ ns(struct sys_mkdir_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_mkdir, 0, 0 },		/* 80 = mkdir */
	{ ns(struct ibcs2_sys_getdents_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_getdents, 0, 0 },	/* 81 = getdents */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 82 = unimplemented libattach */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 83 = unimplemented libdetach */
	{ ns(struct ibcs2_sys_sysfs_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_sysfs, 0, 0 },	/* 84 = sysfs */
	{ ns(struct ibcs2_sys_getmsg_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_getmsg, 0, 0 },	/* 85 = getmsg */
	{ ns(struct ibcs2_sys_putmsg_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_putmsg, 0, 0 },	/* 86 = putmsg */
	{ ns(struct sys_poll_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_poll, 0, 0 },		/* 87 = poll */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 88 = unimplemented unknown */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 89 = unimplemented secure */
	{ ns(struct sys_symlink_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_symlink, 0, 0 },		/* 90 = symlink */
	{ ns(struct ibcs2_sys_lstat_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_lstat, 0, 0 },	/* 91 = lstat */
	{ ns(struct sys_readlink_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_readlink, 0, 0 },	/* 92 = readlink */
	{ ns(struct sys_fchmod_args), 0,
	    (sy_call_t *)sys_fchmod, 0, 0 },		/* 93 = fchmod */
	{ ns(struct sys___posix_fchown_args), 0,
	    (sy_call_t *)sys___posix_fchown, 0, 0 },	/* 94 = fchown */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 95 = unimplemented sigprocmask */
	{ ns(struct compat_16_sys___sigreturn14_args), SYCALL_ARG_PTR,
	    (sy_call_t *)compat_16_sys___sigreturn14, 0, 0 },/* 96 = sigreturn */
	{ ns(struct ibcs2_sys_sigaltstack_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_sigaltstack, 0, 0 },/* 97 = sigaltstack */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 98 = unimplemented sigaction */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 99 = unimplemented sigpending */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 100 = unimplemented getcontext/setcontext/sigsetjmp */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 101 = unimplemented envsys */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 102 = unimplemented evtrapret */
	{ ns(struct ibcs2_sys_statvfs_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_statvfs, 0, 0 },	/* 103 = statvfs */
	{ ns(struct ibcs2_sys_fstatvfs_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_fstatvfs, 0, 0 },	/* 104 = fstatvfs */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 105 = unimplemented isc */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 106 = unimplemented nfssys */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 107 = unimplemented waitsys */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 108 = unimplemented sigsendsys */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 109 = unimplemented hrtsys */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 110 = unimplemented acancel */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 111 = unimplemented async */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 112 = unimplemented priocntlsys */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 113 = unimplemented pathconf */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 114 = unimplemented mincore */
	{ ns(struct ibcs2_sys_mmap_args), 0,
	    (sy_call_t *)ibcs2_sys_mmap, 0, 0 },	/* 115 = mmap */
	{ ns(struct sys_mprotect_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_mprotect, 0, 0 },	/* 116 = mprotect */
	{ ns(struct sys_munmap_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_munmap, 0, 0 },		/* 117 = munmap */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 118 = unimplemented fpathconf */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 119 = unimplemented vfork */
	{ ns(struct sys_fchdir_args), 0,
	    (sy_call_t *)sys_fchdir, 0, 0 },		/* 120 = fchdir */
	{ ns(struct sys_readv_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_readv, 0, 0 },		/* 121 = readv */
	{ ns(struct sys_writev_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys_writev, 0, 0 },		/* 122 = writev */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 123 = unimplemented xstat */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 124 = unimplemented lxstat */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 125 = unimplemented fxstat */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 126 = unimplemented xmknod */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 127 = unimplemented clocal */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 128 = unimplemented setrlimit */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 129 = unimplemented getrlimit */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 130 = unimplemented lchown */
	{ ns(struct ibcs2_sys_memcntl_args), 0,
	    (sy_call_t *)ibcs2_sys_memcntl, 0, 0 },	/* 131 = memcntl */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 132 = unimplemented getpmsg */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 133 = unimplemented putpmsg */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 134 = unimplemented rename */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 135 = unimplemented uname */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 136 = unimplemented setegid */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 137 = unimplemented sysconfig */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 138 = unimplemented adjtime */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 139 = unimplemented systeminfo */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 140 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 141 = unimplemented seteuid */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 142 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 143 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 144 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 145 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 146 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 147 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 148 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 149 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 150 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 151 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 152 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 153 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 154 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 155 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 156 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 157 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 158 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 159 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 160 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 161 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 162 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 163 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 164 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 165 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 166 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 167 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 168 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 169 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 170 = unimplemented */
	{ ns(struct ibcs2_sys_gettimeofday_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_gettimeofday, 0, 0 },/* 171 = gettimeofday */
	{ ns(struct ibcs2_sys_settimeofday_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_settimeofday, 0, 0 },/* 172 = settimeofday */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 173 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 174 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 175 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 176 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 177 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 178 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 179 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 180 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 181 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 182 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 183 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 184 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 185 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 186 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 187 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 188 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 189 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 190 = unimplemented */
	{ ns(struct compat_43_sys_truncate_args), SYCALL_ARG_PTR,
	    (sy_call_t *)compat_43_sys_truncate, 0, 0 },/* 191 = truncate */
	{ ns(struct compat_43_sys_ftruncate_args), 0,
	    (sy_call_t *)compat_43_sys_ftruncate, 0, 0 },/* 192 = ftruncate */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 193 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 194 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 195 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 196 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 197 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 198 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 199 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 200 = unimplemented */
	{ ns(struct xenix_sys_locking_args), 0,
	    (sy_call_t *)xenix_sys_locking, 0, 0 },	/* 201 = locking */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 202 = unimplemented xenix_creatsem */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 203 = unimplemented xenix_opensem */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 204 = unimplemented xenix_sigsem */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 205 = unimplemented xenix_waitsem */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 206 = unimplemented xenix_nbwaitsem */
	{ ns(struct xenix_sys_rdchk_args), 0,
	    (sy_call_t *)xenix_sys_rdchk, 0, 0 },	/* 207 = rdchk */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 208 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 209 = unimplemented */
	{ ns(struct xenix_sys_chsize_args), 0,
	    (sy_call_t *)xenix_sys_chsize, 0, 0 },	/* 210 = chsize */
	{ ns(struct xenix_sys_ftime_args), SYCALL_ARG_PTR,
	    (sy_call_t *)xenix_sys_ftime, 0, 0 },	/* 211 = ftime */
	{ ns(struct xenix_sys_nap_args), 0,
	    (sy_call_t *)xenix_sys_nap, 0, 0 },	/* 212 = nap */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 213 = unimplemented xenix_sdget */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 214 = unimplemented xenix_sdfree */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 215 = unimplemented xenix_sdenter */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 216 = unimplemented xenix_sdleave */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 217 = unimplemented xenix_sdgetv */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 218 = unimplemented xenix_sdwaitv */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 219 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 220 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 221 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 222 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 223 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 224 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 225 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 226 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 227 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 228 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 229 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 230 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 231 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 232 = unimplemented xenix_proctl */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 233 = unimplemented xenix_execseg */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 234 = unimplemented xenix_unexecseg */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 235 = unimplemented */
	{ ns(struct compat_50_sys_select_args), SYCALL_ARG_PTR,
	    (sy_call_t *)compat_50_sys_select, 0, 0 },/* 236 = select */
	{ ns(struct ibcs2_sys_eaccess_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_eaccess, 0, 0 },	/* 237 = eaccess */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 238 = unimplemented xenix_paccess */
	{ ns(struct ibcs2_sys_sigaction_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_sigaction, 0, 0 },	/* 239 = sigaction */
	{ ns(struct ibcs2_sys_sigprocmask_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_sigprocmask, 0, 0 },/* 240 = sigprocmask */
	{ ns(struct ibcs2_sys_sigpending_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_sigpending, 0, 0 },/* 241 = sigpending */
	{ ns(struct ibcs2_sys_sigsuspend_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_sigsuspend, 0, 0 },/* 242 = sigsuspend */
	{ ns(struct ibcs2_sys_getgroups_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_getgroups, 0, 0 },	/* 243 = getgroups */
	{ ns(struct ibcs2_sys_setgroups_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_setgroups, 0, 0 },	/* 244 = setgroups */
	{ ns(struct ibcs2_sys_sysconf_args), 0,
	    (sy_call_t *)ibcs2_sys_sysconf, 0, 0 },	/* 245 = sysconf */
	{ ns(struct ibcs2_sys_pathconf_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_pathconf, 0, 0 },	/* 246 = pathconf */
	{ ns(struct ibcs2_sys_fpathconf_args), 0,
	    (sy_call_t *)ibcs2_sys_fpathconf, 0, 0 },	/* 247 = fpathconf */
	{ ns(struct sys___posix_rename_args), SYCALL_ARG_PTR,
	    (sy_call_t *)sys___posix_rename, 0, 0 },	/* 248 = __posix_rename */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 249 = unimplemented */
	{ ns(struct ibcs2_sys_scoinfo_args), SYCALL_ARG_PTR,
	    (sy_call_t *)ibcs2_sys_scoinfo, 0, 0 },	/* 250 = scoinfo */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 251 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 252 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 253 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 254 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 255 = unimplemented getitimer */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 256 = unimplemented setitimer */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 257 = unimplemented */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 258 = unimplemented setreuid */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 259 = unimplemented setregid */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 260 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 261 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 262 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 263 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 264 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 265 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 266 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 267 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 268 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 269 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 270 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 271 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 272 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 273 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 274 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 275 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 276 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 277 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 278 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 279 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 280 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 281 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 282 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 283 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 284 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 285 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 286 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 287 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 288 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 289 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 290 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 291 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 292 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 293 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 294 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 295 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 296 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 297 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 298 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 299 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 300 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 301 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 302 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 303 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 304 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 305 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 306 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 307 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 308 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 309 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 310 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 311 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 312 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 313 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 314 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 315 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 316 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 317 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 318 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 319 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 320 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 321 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 322 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 323 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 324 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 325 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 326 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 327 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 328 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 329 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 330 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 331 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 332 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 333 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 334 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 335 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 336 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 337 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 338 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 339 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 340 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 341 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 342 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 343 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 344 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 345 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 346 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 347 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 348 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 349 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 350 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 351 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 352 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 353 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 354 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 355 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 356 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 357 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 358 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 359 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 360 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 361 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 362 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 363 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 364 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 365 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 366 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 367 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 368 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 369 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 370 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 371 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 372 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 373 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 374 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 375 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 376 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 377 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 378 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 379 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 380 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 381 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 382 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 383 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 384 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 385 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 386 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 387 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 388 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 389 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 390 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 391 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 392 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 393 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 394 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 395 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 396 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 397 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 398 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 399 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 400 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 401 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 402 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 403 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 404 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 405 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 406 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 407 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 408 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 409 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 410 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 411 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 412 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 413 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 414 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 415 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 416 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 417 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 418 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 419 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 420 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 421 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 422 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 423 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 424 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 425 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 426 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 427 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 428 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 429 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 430 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 431 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 432 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 433 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 434 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 435 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 436 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 437 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 438 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 439 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 440 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 441 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 442 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 443 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 444 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 445 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 446 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 447 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 448 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 449 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 450 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 451 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 452 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 453 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 454 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 455 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 456 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 457 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 458 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 459 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 460 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 461 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 462 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 463 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 464 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 465 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 466 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 467 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 468 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 469 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 470 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 471 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 472 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 473 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 474 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 475 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 476 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 477 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 478 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 479 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 480 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 481 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 482 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 483 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 484 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 485 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 486 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 487 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 488 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 489 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 490 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 491 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 492 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 493 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 494 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 495 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 496 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 497 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 498 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 499 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 500 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 501 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 502 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 503 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 504 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 505 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 506 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 507 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 508 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 509 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 510 = filler */
	{ 0, 0, 0,
	    sys_nosys, 0, 0 },			/* 511 = filler */
};
