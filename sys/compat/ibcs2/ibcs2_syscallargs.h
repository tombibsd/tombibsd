/* $NetBSD$ */

/*
 * System call argument lists.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from	NetBSD: syscalls.master,v 1.41 2013/11/07 19:37:18 njoly Exp
 */

#ifndef _IBCS2_SYS_SYSCALLARGS_H_
#define	_IBCS2_SYS_SYSCALLARGS_H_

#define	IBCS2_SYS_MAXSYSARGS	8

#undef	syscallarg
#define	syscallarg(x)							\
	union {								\
		register_t pad;						\
		struct { x datum; } le;					\
		struct { /* LINTED zero array dimension */		\
			int8_t pad[  /* CONSTCOND */			\
				(sizeof (register_t) < sizeof (x))	\
				? 0					\
				: sizeof (register_t) - sizeof (x)];	\
			x datum;					\
		} be;							\
	}

#undef check_syscall_args
#define check_syscall_args(call) /*LINTED*/ \
	typedef char call##_check_args[sizeof (struct call##_args) \
		<= IBCS2_SYS_MAXSYSARGS * sizeof (register_t) ? 1 : -1];

struct sys_exit_args;

struct ibcs2_sys_read_args {
	syscallarg(int) fd;
	syscallarg(char *) buf;
	syscallarg(u_int) nbytes;
};
check_syscall_args(ibcs2_sys_read)

struct sys_write_args;

struct ibcs2_sys_open_args {
	syscallarg(const char *) path;
	syscallarg(int) flags;
	syscallarg(int) mode;
};
check_syscall_args(ibcs2_sys_open)

struct sys_close_args;

struct ibcs2_sys_waitsys_args {
	syscallarg(int) a1;
	syscallarg(int) a2;
	syscallarg(int) a3;
};
check_syscall_args(ibcs2_sys_waitsys)

struct ibcs2_sys_creat_args {
	syscallarg(const char *) path;
	syscallarg(int) mode;
};
check_syscall_args(ibcs2_sys_creat)

struct sys_link_args;

struct sys_unlink_args;

struct ibcs2_sys_execv_args {
	syscallarg(const char *) path;
	syscallarg(char **) argp;
};
check_syscall_args(ibcs2_sys_execv)

struct sys_chdir_args;

struct ibcs2_sys_time_args {
	syscallarg(ibcs2_time_t *) tp;
};
check_syscall_args(ibcs2_sys_time)

struct ibcs2_sys_mknod_args {
	syscallarg(const char *) path;
	syscallarg(int) mode;
	syscallarg(int) dev;
};
check_syscall_args(ibcs2_sys_mknod)

struct sys_chmod_args;

struct sys___posix_chown_args;

struct sys_obreak_args;

struct ibcs2_sys_stat_args {
	syscallarg(const char *) path;
	syscallarg(struct ibcs2_stat *) st;
};
check_syscall_args(ibcs2_sys_stat)

struct compat_43_sys_lseek_args;

struct ibcs2_sys_mount_args {
	syscallarg(char *) special;
	syscallarg(char *) dir;
	syscallarg(int) flags;
	syscallarg(int) fstype;
	syscallarg(char *) data;
	syscallarg(int) len;
};
check_syscall_args(ibcs2_sys_mount)

struct ibcs2_sys_umount_args {
	syscallarg(char *) name;
};
check_syscall_args(ibcs2_sys_umount)

struct ibcs2_sys_setuid_args {
	syscallarg(int) uid;
};
check_syscall_args(ibcs2_sys_setuid)

struct ibcs2_sys_stime_args {
	syscallarg(long *) timep;
};
check_syscall_args(ibcs2_sys_stime)

struct ibcs2_sys_alarm_args {
	syscallarg(unsigned) sec;
};
check_syscall_args(ibcs2_sys_alarm)

struct ibcs2_sys_fstat_args {
	syscallarg(int) fd;
	syscallarg(struct ibcs2_stat *) st;
};
check_syscall_args(ibcs2_sys_fstat)

struct ibcs2_sys_utime_args {
	syscallarg(const char *) path;
	syscallarg(struct ibcs2_utimbuf *) buf;
};
check_syscall_args(ibcs2_sys_utime)

struct ibcs2_sys_gtty_args {
	syscallarg(int) fd;
	syscallarg(struct ibcs2_sgttyb *) tb;
};
check_syscall_args(ibcs2_sys_gtty)

struct ibcs2_sys_access_args {
	syscallarg(const char *) path;
	syscallarg(int) flags;
};
check_syscall_args(ibcs2_sys_access)

struct ibcs2_sys_nice_args {
	syscallarg(int) incr;
};
check_syscall_args(ibcs2_sys_nice)

struct ibcs2_sys_statfs_args {
	syscallarg(const char *) path;
	syscallarg(struct ibcs2_statfs *) buf;
	syscallarg(int) len;
	syscallarg(int) fstype;
};
check_syscall_args(ibcs2_sys_statfs)

struct ibcs2_sys_kill_args {
	syscallarg(int) pid;
	syscallarg(int) signo;
};
check_syscall_args(ibcs2_sys_kill)

struct ibcs2_sys_fstatfs_args {
	syscallarg(int) fd;
	syscallarg(struct ibcs2_statfs *) buf;
	syscallarg(int) len;
	syscallarg(int) fstype;
};
check_syscall_args(ibcs2_sys_fstatfs)

struct ibcs2_sys_pgrpsys_args {
	syscallarg(int) type;
	syscallarg(void *) dummy;
	syscallarg(int) pid;
	syscallarg(int) pgid;
};
check_syscall_args(ibcs2_sys_pgrpsys)

struct sys_dup_args;

struct ibcs2_sys_times_args {
	syscallarg(struct tms *) tp;
};
check_syscall_args(ibcs2_sys_times)

struct ibcs2_sys_plock_args {
	syscallarg(int) cmd;
};
check_syscall_args(ibcs2_sys_plock)

struct ibcs2_sys_setgid_args {
	syscallarg(int) gid;
};
check_syscall_args(ibcs2_sys_setgid)

struct ibcs2_sys_sigsys_args {
	syscallarg(int) sig;
	syscallarg(ibcs2_sig_t) fp;
};
check_syscall_args(ibcs2_sys_sigsys)
#ifdef SYSVMSG

struct ibcs2_sys_msgsys_args {
	syscallarg(int) which;
	syscallarg(int) a2;
	syscallarg(int) a3;
	syscallarg(int) a4;
	syscallarg(int) a5;
	syscallarg(int) a6;
};
check_syscall_args(ibcs2_sys_msgsys)
#else
#endif

struct ibcs2_sys_sysmachine_args {
	syscallarg(int) cmd;
	syscallarg(int) arg;
};
check_syscall_args(ibcs2_sys_sysmachine)
#ifdef SYSVSHM

struct ibcs2_sys_shmsys_args {
	syscallarg(int) which;
	syscallarg(int) a2;
	syscallarg(int) a3;
	syscallarg(int) a4;
};
check_syscall_args(ibcs2_sys_shmsys)
#else
#endif
#ifdef SYSVSEM

struct ibcs2_sys_semsys_args {
	syscallarg(int) which;
	syscallarg(int) a2;
	syscallarg(int) a3;
	syscallarg(int) a4;
	syscallarg(int) a5;
};
check_syscall_args(ibcs2_sys_semsys)
#else
#endif

struct ibcs2_sys_ioctl_args {
	syscallarg(int) fd;
	syscallarg(int) cmd;
	syscallarg(void *) data;
};
check_syscall_args(ibcs2_sys_ioctl)

struct ibcs2_sys_uadmin_args {
	syscallarg(int) cmd;
	syscallarg(int) func;
	syscallarg(void *) data;
};
check_syscall_args(ibcs2_sys_uadmin)

struct ibcs2_sys_utssys_args {
	syscallarg(int) a1;
	syscallarg(int) a2;
	syscallarg(int) flag;
};
check_syscall_args(ibcs2_sys_utssys)

struct sys_fsync_args;

struct ibcs2_sys_execve_args {
	syscallarg(const char *) path;
	syscallarg(char **) argp;
	syscallarg(char **) envp;
};
check_syscall_args(ibcs2_sys_execve)

struct sys_umask_args;

struct sys_chroot_args;

struct ibcs2_sys_fcntl_args {
	syscallarg(int) fd;
	syscallarg(int) cmd;
	syscallarg(char *) arg;
};
check_syscall_args(ibcs2_sys_fcntl)

struct ibcs2_sys_ulimit_args {
	syscallarg(int) cmd;
	syscallarg(int) newlimit;
};
check_syscall_args(ibcs2_sys_ulimit)

struct sys_rmdir_args;

struct sys_mkdir_args;

struct ibcs2_sys_getdents_args {
	syscallarg(int) fd;
	syscallarg(char *) buf;
	syscallarg(int) nbytes;
};
check_syscall_args(ibcs2_sys_getdents)

struct ibcs2_sys_sysfs_args {
	syscallarg(int) cmd;
	syscallarg(void *) d1;
	syscallarg(char *) buf;
};
check_syscall_args(ibcs2_sys_sysfs)

struct ibcs2_sys_getmsg_args {
	syscallarg(int) fd;
	syscallarg(struct ibcs2_stropts *) ctl;
	syscallarg(struct ibcs2_stropts *) dat;
	syscallarg(int *) flags;
};
check_syscall_args(ibcs2_sys_getmsg)

struct ibcs2_sys_putmsg_args {
	syscallarg(int) fd;
	syscallarg(struct ibcs2_stropts *) ctl;
	syscallarg(struct ibcs2_stropts *) dat;
	syscallarg(int) flags;
};
check_syscall_args(ibcs2_sys_putmsg)

struct sys_poll_args;

struct sys_symlink_args;

struct ibcs2_sys_lstat_args {
	syscallarg(const char *) path;
	syscallarg(struct ibcs2_stat *) st;
};
check_syscall_args(ibcs2_sys_lstat)

struct sys_readlink_args;

struct sys_fchmod_args;

struct sys___posix_fchown_args;

struct compat_16_sys___sigreturn14_args;

struct ibcs2_sys_sigaltstack_args {
	syscallarg(const struct ibcs2_sigaltstack *) nss;
	syscallarg(struct ibcs2_sigaltstack *) oss;
};
check_syscall_args(ibcs2_sys_sigaltstack)

struct ibcs2_sys_statvfs_args {
	syscallarg(const char *) path;
	syscallarg(struct ibcs2_statvfs *) buf;
};
check_syscall_args(ibcs2_sys_statvfs)

struct ibcs2_sys_fstatvfs_args {
	syscallarg(int) fd;
	syscallarg(struct ibcs2_statvfs *) buf;
};
check_syscall_args(ibcs2_sys_fstatvfs)

struct ibcs2_sys_mmap_args {
	syscallarg(ibcs2_caddr_t) addr;
	syscallarg(ibcs2_size_t) len;
	syscallarg(int) prot;
	syscallarg(int) flags;
	syscallarg(int) fd;
	syscallarg(ibcs2_off_t) off;
};
check_syscall_args(ibcs2_sys_mmap)

struct sys_mprotect_args;

struct sys_munmap_args;

struct sys_fchdir_args;

struct sys_readv_args;

struct sys_writev_args;

struct ibcs2_sys_memcntl_args {
	syscallarg(ibcs2_caddr_t) addr;
	syscallarg(ibcs2_size_t) len;
	syscallarg(int) cmd;
	syscallarg(ibcs2_caddr_t) arg;
	syscallarg(int) attr;
	syscallarg(int) mask;
};
check_syscall_args(ibcs2_sys_memcntl)

struct ibcs2_sys_gettimeofday_args {
	syscallarg(struct timeval50 *) tp;
};
check_syscall_args(ibcs2_sys_gettimeofday)

struct ibcs2_sys_settimeofday_args {
	syscallarg(struct timeval50 *) tp;
};
check_syscall_args(ibcs2_sys_settimeofday)

struct compat_43_sys_truncate_args;

struct compat_43_sys_ftruncate_args;

struct xenix_sys_locking_args {
	syscallarg(int) fd;
	syscallarg(int) blk;
	syscallarg(int) size;
};
check_syscall_args(xenix_sys_locking)

struct xenix_sys_rdchk_args {
	syscallarg(int) fd;
};
check_syscall_args(xenix_sys_rdchk)

struct xenix_sys_chsize_args {
	syscallarg(int) fd;
	syscallarg(long) size;
};
check_syscall_args(xenix_sys_chsize)

struct xenix_sys_ftime_args {
	syscallarg(struct xenix_timeb *) tp;
};
check_syscall_args(xenix_sys_ftime)

struct xenix_sys_nap_args {
	syscallarg(long) millisec;
};
check_syscall_args(xenix_sys_nap)

struct compat_50_sys_select_args;

struct ibcs2_sys_eaccess_args {
	syscallarg(const char *) path;
	syscallarg(int) flags;
};
check_syscall_args(ibcs2_sys_eaccess)

struct ibcs2_sys_sigaction_args {
	syscallarg(int) signum;
	syscallarg(const struct ibcs2_sigaction *) nsa;
	syscallarg(struct ibcs2_sigaction *) osa;
};
check_syscall_args(ibcs2_sys_sigaction)

struct ibcs2_sys_sigprocmask_args {
	syscallarg(int) how;
	syscallarg(const ibcs2_sigset_t *) set;
	syscallarg(ibcs2_sigset_t *) oset;
};
check_syscall_args(ibcs2_sys_sigprocmask)

struct ibcs2_sys_sigpending_args {
	syscallarg(ibcs2_sigset_t *) set;
};
check_syscall_args(ibcs2_sys_sigpending)

struct ibcs2_sys_sigsuspend_args {
	syscallarg(const ibcs2_sigset_t *) set;
};
check_syscall_args(ibcs2_sys_sigsuspend)

struct ibcs2_sys_getgroups_args {
	syscallarg(int) gidsetsize;
	syscallarg(ibcs2_gid_t *) gidset;
};
check_syscall_args(ibcs2_sys_getgroups)

struct ibcs2_sys_setgroups_args {
	syscallarg(int) gidsetsize;
	syscallarg(ibcs2_gid_t *) gidset;
};
check_syscall_args(ibcs2_sys_setgroups)

struct ibcs2_sys_sysconf_args {
	syscallarg(int) name;
};
check_syscall_args(ibcs2_sys_sysconf)

struct ibcs2_sys_pathconf_args {
	syscallarg(char *) path;
	syscallarg(int) name;
};
check_syscall_args(ibcs2_sys_pathconf)

struct ibcs2_sys_fpathconf_args {
	syscallarg(int) fd;
	syscallarg(int) name;
};
check_syscall_args(ibcs2_sys_fpathconf)

struct sys___posix_rename_args;

struct ibcs2_sys_scoinfo_args {
	syscallarg(struct scoutsname *) bp;
	syscallarg(int) len;
};
check_syscall_args(ibcs2_sys_scoinfo)

/*
 * System call prototypes.
 */

int	sys_nosys(struct lwp *, const void *, register_t *);

int	sys_exit(struct lwp *, const struct sys_exit_args *, register_t *);

int	sys_fork(struct lwp *, const void *, register_t *);

int	ibcs2_sys_read(struct lwp *, const struct ibcs2_sys_read_args *, register_t *);

int	sys_write(struct lwp *, const struct sys_write_args *, register_t *);

int	ibcs2_sys_open(struct lwp *, const struct ibcs2_sys_open_args *, register_t *);

int	sys_close(struct lwp *, const struct sys_close_args *, register_t *);

int	ibcs2_sys_waitsys(struct lwp *, const struct ibcs2_sys_waitsys_args *, register_t *);

int	ibcs2_sys_creat(struct lwp *, const struct ibcs2_sys_creat_args *, register_t *);

int	sys_link(struct lwp *, const struct sys_link_args *, register_t *);

int	sys_unlink(struct lwp *, const struct sys_unlink_args *, register_t *);

int	ibcs2_sys_execv(struct lwp *, const struct ibcs2_sys_execv_args *, register_t *);

int	sys_chdir(struct lwp *, const struct sys_chdir_args *, register_t *);

int	ibcs2_sys_time(struct lwp *, const struct ibcs2_sys_time_args *, register_t *);

int	ibcs2_sys_mknod(struct lwp *, const struct ibcs2_sys_mknod_args *, register_t *);

int	sys_chmod(struct lwp *, const struct sys_chmod_args *, register_t *);

int	sys___posix_chown(struct lwp *, const struct sys___posix_chown_args *, register_t *);

int	sys_obreak(struct lwp *, const struct sys_obreak_args *, register_t *);

int	ibcs2_sys_stat(struct lwp *, const struct ibcs2_sys_stat_args *, register_t *);

int	compat_43_sys_lseek(struct lwp *, const struct compat_43_sys_lseek_args *, register_t *);

int	sys_getpid_with_ppid(struct lwp *, const void *, register_t *);

int	ibcs2_sys_mount(struct lwp *, const struct ibcs2_sys_mount_args *, register_t *);

int	ibcs2_sys_umount(struct lwp *, const struct ibcs2_sys_umount_args *, register_t *);

int	ibcs2_sys_setuid(struct lwp *, const struct ibcs2_sys_setuid_args *, register_t *);

int	sys_getuid_with_euid(struct lwp *, const void *, register_t *);

int	ibcs2_sys_stime(struct lwp *, const struct ibcs2_sys_stime_args *, register_t *);

int	ibcs2_sys_alarm(struct lwp *, const struct ibcs2_sys_alarm_args *, register_t *);

int	ibcs2_sys_fstat(struct lwp *, const struct ibcs2_sys_fstat_args *, register_t *);

int	ibcs2_sys_pause(struct lwp *, const void *, register_t *);

int	ibcs2_sys_utime(struct lwp *, const struct ibcs2_sys_utime_args *, register_t *);

int	ibcs2_sys_gtty(struct lwp *, const struct ibcs2_sys_gtty_args *, register_t *);

int	ibcs2_sys_access(struct lwp *, const struct ibcs2_sys_access_args *, register_t *);

int	ibcs2_sys_nice(struct lwp *, const struct ibcs2_sys_nice_args *, register_t *);

int	ibcs2_sys_statfs(struct lwp *, const struct ibcs2_sys_statfs_args *, register_t *);

int	sys_sync(struct lwp *, const void *, register_t *);

int	ibcs2_sys_kill(struct lwp *, const struct ibcs2_sys_kill_args *, register_t *);

int	ibcs2_sys_fstatfs(struct lwp *, const struct ibcs2_sys_fstatfs_args *, register_t *);

int	ibcs2_sys_pgrpsys(struct lwp *, const struct ibcs2_sys_pgrpsys_args *, register_t *);

int	sys_dup(struct lwp *, const struct sys_dup_args *, register_t *);

int	sys_pipe(struct lwp *, const void *, register_t *);

int	ibcs2_sys_times(struct lwp *, const struct ibcs2_sys_times_args *, register_t *);

int	ibcs2_sys_plock(struct lwp *, const struct ibcs2_sys_plock_args *, register_t *);

int	ibcs2_sys_setgid(struct lwp *, const struct ibcs2_sys_setgid_args *, register_t *);

int	sys_getgid_with_egid(struct lwp *, const void *, register_t *);

int	ibcs2_sys_sigsys(struct lwp *, const struct ibcs2_sys_sigsys_args *, register_t *);

#ifdef SYSVMSG
int	ibcs2_sys_msgsys(struct lwp *, const struct ibcs2_sys_msgsys_args *, register_t *);

#else
#endif
int	ibcs2_sys_sysmachine(struct lwp *, const struct ibcs2_sys_sysmachine_args *, register_t *);

#ifdef SYSVSHM
int	ibcs2_sys_shmsys(struct lwp *, const struct ibcs2_sys_shmsys_args *, register_t *);

#else
#endif
#ifdef SYSVSEM
int	ibcs2_sys_semsys(struct lwp *, const struct ibcs2_sys_semsys_args *, register_t *);

#else
#endif
int	ibcs2_sys_ioctl(struct lwp *, const struct ibcs2_sys_ioctl_args *, register_t *);

int	ibcs2_sys_uadmin(struct lwp *, const struct ibcs2_sys_uadmin_args *, register_t *);

int	ibcs2_sys_utssys(struct lwp *, const struct ibcs2_sys_utssys_args *, register_t *);

int	sys_fsync(struct lwp *, const struct sys_fsync_args *, register_t *);

int	ibcs2_sys_execve(struct lwp *, const struct ibcs2_sys_execve_args *, register_t *);

int	sys_umask(struct lwp *, const struct sys_umask_args *, register_t *);

int	sys_chroot(struct lwp *, const struct sys_chroot_args *, register_t *);

int	ibcs2_sys_fcntl(struct lwp *, const struct ibcs2_sys_fcntl_args *, register_t *);

int	ibcs2_sys_ulimit(struct lwp *, const struct ibcs2_sys_ulimit_args *, register_t *);

int	sys_rmdir(struct lwp *, const struct sys_rmdir_args *, register_t *);

int	sys_mkdir(struct lwp *, const struct sys_mkdir_args *, register_t *);

int	ibcs2_sys_getdents(struct lwp *, const struct ibcs2_sys_getdents_args *, register_t *);

int	ibcs2_sys_sysfs(struct lwp *, const struct ibcs2_sys_sysfs_args *, register_t *);

int	ibcs2_sys_getmsg(struct lwp *, const struct ibcs2_sys_getmsg_args *, register_t *);

int	ibcs2_sys_putmsg(struct lwp *, const struct ibcs2_sys_putmsg_args *, register_t *);

int	sys_poll(struct lwp *, const struct sys_poll_args *, register_t *);

int	sys_symlink(struct lwp *, const struct sys_symlink_args *, register_t *);

int	ibcs2_sys_lstat(struct lwp *, const struct ibcs2_sys_lstat_args *, register_t *);

int	sys_readlink(struct lwp *, const struct sys_readlink_args *, register_t *);

int	sys_fchmod(struct lwp *, const struct sys_fchmod_args *, register_t *);

int	sys___posix_fchown(struct lwp *, const struct sys___posix_fchown_args *, register_t *);

int	compat_16_sys___sigreturn14(struct lwp *, const struct compat_16_sys___sigreturn14_args *, register_t *);

int	ibcs2_sys_sigaltstack(struct lwp *, const struct ibcs2_sys_sigaltstack_args *, register_t *);

int	ibcs2_sys_statvfs(struct lwp *, const struct ibcs2_sys_statvfs_args *, register_t *);

int	ibcs2_sys_fstatvfs(struct lwp *, const struct ibcs2_sys_fstatvfs_args *, register_t *);

int	ibcs2_sys_mmap(struct lwp *, const struct ibcs2_sys_mmap_args *, register_t *);

int	sys_mprotect(struct lwp *, const struct sys_mprotect_args *, register_t *);

int	sys_munmap(struct lwp *, const struct sys_munmap_args *, register_t *);

int	sys_fchdir(struct lwp *, const struct sys_fchdir_args *, register_t *);

int	sys_readv(struct lwp *, const struct sys_readv_args *, register_t *);

int	sys_writev(struct lwp *, const struct sys_writev_args *, register_t *);

int	ibcs2_sys_memcntl(struct lwp *, const struct ibcs2_sys_memcntl_args *, register_t *);

int	ibcs2_sys_gettimeofday(struct lwp *, const struct ibcs2_sys_gettimeofday_args *, register_t *);

int	ibcs2_sys_settimeofday(struct lwp *, const struct ibcs2_sys_settimeofday_args *, register_t *);

int	compat_43_sys_truncate(struct lwp *, const struct compat_43_sys_truncate_args *, register_t *);

int	compat_43_sys_ftruncate(struct lwp *, const struct compat_43_sys_ftruncate_args *, register_t *);

int	xenix_sys_locking(struct lwp *, const struct xenix_sys_locking_args *, register_t *);

int	xenix_sys_rdchk(struct lwp *, const struct xenix_sys_rdchk_args *, register_t *);

int	xenix_sys_chsize(struct lwp *, const struct xenix_sys_chsize_args *, register_t *);

int	xenix_sys_ftime(struct lwp *, const struct xenix_sys_ftime_args *, register_t *);

int	xenix_sys_nap(struct lwp *, const struct xenix_sys_nap_args *, register_t *);

int	compat_50_sys_select(struct lwp *, const struct compat_50_sys_select_args *, register_t *);

int	ibcs2_sys_eaccess(struct lwp *, const struct ibcs2_sys_eaccess_args *, register_t *);

int	ibcs2_sys_sigaction(struct lwp *, const struct ibcs2_sys_sigaction_args *, register_t *);

int	ibcs2_sys_sigprocmask(struct lwp *, const struct ibcs2_sys_sigprocmask_args *, register_t *);

int	ibcs2_sys_sigpending(struct lwp *, const struct ibcs2_sys_sigpending_args *, register_t *);

int	ibcs2_sys_sigsuspend(struct lwp *, const struct ibcs2_sys_sigsuspend_args *, register_t *);

int	ibcs2_sys_getgroups(struct lwp *, const struct ibcs2_sys_getgroups_args *, register_t *);

int	ibcs2_sys_setgroups(struct lwp *, const struct ibcs2_sys_setgroups_args *, register_t *);

int	ibcs2_sys_sysconf(struct lwp *, const struct ibcs2_sys_sysconf_args *, register_t *);

int	ibcs2_sys_pathconf(struct lwp *, const struct ibcs2_sys_pathconf_args *, register_t *);

int	ibcs2_sys_fpathconf(struct lwp *, const struct ibcs2_sys_fpathconf_args *, register_t *);

int	sys___posix_rename(struct lwp *, const struct sys___posix_rename_args *, register_t *);

int	ibcs2_sys_scoinfo(struct lwp *, const struct ibcs2_sys_scoinfo_args *, register_t *);

#endif /* _IBCS2_SYS_SYSCALLARGS_H_ */
