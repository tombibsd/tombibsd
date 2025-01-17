/* $NetBSD$ */

/*
 * System call names.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from	NetBSD: syscalls.master,v 1.89 2014/11/22 13:18:45 njoly Exp
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

#if defined(_KERNEL_OPT)
#if defined(_KERNEL_OPT)
#include "opt_compat_netbsd.h"
#include "opt_compat_43.h"
#endif
#include <sys/param.h>
#include <sys/poll.h>
#include <sys/systm.h>
#include <sys/signal.h>
#include <sys/mount.h>
#include <sys/sched.h>
#include <sys/syscallargs.h>
#include <compat/linux/common/linux_types.h>
#include <compat/linux/common/linux_signal.h>
#include <compat/linux/common/linux_siginfo.h>
#include <compat/linux/common/linux_machdep.h>
#include <compat/linux/common/linux_mmap.h>
#include <compat/linux/linux_syscallargs.h>
#endif /* _KERNEL_OPT */

const char *const linux_syscallnames[] = {
	/*   0 */	"syscall",
	/*   1 */	"exit",
	/*   2 */	"fork",
	/*   3 */	"read",
	/*   4 */	"write",
	/*   5 */	"open",
	/*   6 */	"close",
	/*   7 */	"waitpid",
	/*   8 */	"creat",
	/*   9 */	"link",
	/*  10 */	"unlink",
	/*  11 */	"execve",
	/*  12 */	"chdir",
	/*  13 */	"time",
	/*  14 */	"mknod",
	/*  15 */	"chmod",
	/*  16 */	"chown16",
	/*  17 */	"#17 (obsolete break)",
	/*  18 */	"#18 (obsolete ostat)",
#if !defined(_KERNEL) || defined(COMPAT_43)
	/*  19 */	"lseek",
#else
	/*  19 */	"#19 (unimplemented compat_43_sys_lseek)",
#endif
	/*  20 */	"getpid",
	/*  21 */	"#21 (unimplemented mount)",
	/*  22 */	"#22 (obsolete umount)",
	/*  23 */	"linux_setuid16",
	/*  24 */	"linux_getuid16",
	/*  25 */	"stime",
	/*  26 */	"ptrace",
	/*  27 */	"alarm",
	/*  28 */	"#28 (obsolete ofstat)",
	/*  29 */	"pause",
	/*  30 */	"utime",
	/*  31 */	"#31 (obsolete stty)",
	/*  32 */	"#32 (obsolete gtty)",
	/*  33 */	"access",
	/*  34 */	"nice",
	/*  35 */	"#35 (obsolete ftime)",
	/*  36 */	"sync",
	/*  37 */	"kill",
	/*  38 */	"__posix_rename",
	/*  39 */	"mkdir",
	/*  40 */	"rmdir",
	/*  41 */	"dup",
	/*  42 */	"pipe",
	/*  43 */	"times",
	/*  44 */	"#44 (obsolete prof)",
	/*  45 */	"brk",
	/*  46 */	"linux_setgid16",
	/*  47 */	"linux_getgid16",
	/*  48 */	"signal",
	/*  49 */	"linux_geteuid16",
	/*  50 */	"linux_getegid16",
	/*  51 */	"acct",
	/*  52 */	"#52 (unimplemented umount)",
	/*  53 */	"#53 (obsolete lock)",
	/*  54 */	"ioctl",
	/*  55 */	"fcntl",
	/*  56 */	"#56 (obsolete mpx)",
	/*  57 */	"setpgid",
	/*  58 */	"#58 (obsolete ulimit)",
	/*  59 */	"#59 (unimplemented oldolduname)",
	/*  60 */	"umask",
	/*  61 */	"chroot",
	/*  62 */	"#62 (unimplemented ustat)",
	/*  63 */	"dup2",
	/*  64 */	"getppid",
	/*  65 */	"getpgrp",
	/*  66 */	"setsid",
	/*  67 */	"sigaction",
	/*  68 */	"siggetmask",
	/*  69 */	"sigsetmask",
	/*  70 */	"setreuid16",
	/*  71 */	"setregid16",
	/*  72 */	"sigsuspend",
	/*  73 */	"sigpending",
#if !defined(_KERNEL) || defined(COMPAT_43)
	/*  74 */	"sethostname",
#else
	/*  74 */	"#74 (unimplemented compat_43_sys_sethostname)",
#endif
	/*  75 */	"setrlimit",
	/*  76 */	"getrlimit",
	/*  77 */	"getrusage",
	/*  78 */	"gettimeofday",
	/*  79 */	"settimeofday",
	/*  80 */	"getgroups16",
	/*  81 */	"setgroups16",
	/*  82 */	"oldselect",
	/*  83 */	"symlink",
#if !defined(_KERNEL) || defined(COMPAT_43)
	/*  84 */	"oolstat",
#else
	/*  84 */	"#84 (unimplemented compat_43_sys_lstat)",
#endif
	/*  85 */	"readlink",
#ifdef EXEC_AOUT
	/*  86 */	"uselib",
#else
	/*  86 */	"#86 (unimplemented sys_uselib)",
#endif
	/*  87 */	"swapon",
	/*  88 */	"reboot",
	/*  89 */	"readdir",
	/*  90 */	"old_mmap",
	/*  91 */	"munmap",
	/*  92 */	"truncate",
#if !defined(_KERNEL) || defined(COMPAT_43)
	/*  93 */	"ftruncate",
#else
	/*  93 */	"#93 (unimplemented compat_43_sys_ftruncate)",
#endif
	/*  94 */	"fchmod",
	/*  95 */	"fchown16",
	/*  96 */	"getpriority",
	/*  97 */	"setpriority",
	/*  98 */	"profil",
	/*  99 */	"statfs",
	/* 100 */	"fstatfs",
	/* 101 */	"#101 (unimplemented ioperm)",
	/* 102 */	"socketcall",
	/* 103 */	"#103 (unimplemented syslog)",
	/* 104 */	"setitimer",
	/* 105 */	"getitimer",
	/* 106 */	"stat",
	/* 107 */	"lstat",
	/* 108 */	"fstat",
	/* 109 */	"#109 (unimplemented olduname)",
	/* 110 */	"#110 (unimplemented iopl)",
	/* 111 */	"#111 (unimplemented vhangup)",
	/* 112 */	"#112 (unimplemented idle)",
	/* 113 */	"#113 (unimplemented vm86old)",
	/* 114 */	"wait4",
	/* 115 */	"swapoff",
	/* 116 */	"sysinfo",
	/* 117 */	"ipc",
	/* 118 */	"fsync",
	/* 119 */	"sigreturn",
	/* 120 */	"clone",
	/* 121 */	"setdomainname",
	/* 122 */	"uname",
	/* 123 */	"cacheflush",
	/* 124 */	"#124 (unimplemented adjtimex)",
	/* 125 */	"mprotect",
	/* 126 */	"sigprocmask",
	/* 127 */	"#127 (unimplemented create_module)",
	/* 128 */	"#128 (unimplemented init_module)",
	/* 129 */	"#129 (unimplemented delete_module)",
	/* 130 */	"#130 (unimplemented get_kernel_syms)",
	/* 131 */	"#131 (unimplemented quotactl)",
	/* 132 */	"getpgid",
	/* 133 */	"fchdir",
	/* 134 */	"#134 (unimplemented bdflush)",
	/* 135 */	"#135 (unimplemented sysfs)",
	/* 136 */	"personality",
	/* 137 */	"#137 (unimplemented afs_syscall)",
	/* 138 */	"linux_setfsuid16",
	/* 139 */	"linux_setfsgid16",
	/* 140 */	"llseek",
	/* 141 */	"getdents",
	/* 142 */	"select",
	/* 143 */	"flock",
	/* 144 */	"__msync13",
	/* 145 */	"readv",
	/* 146 */	"writev",
	/* 147 */	"getsid",
	/* 148 */	"fdatasync",
	/* 149 */	"__sysctl",
	/* 150 */	"mlock",
	/* 151 */	"munlock",
	/* 152 */	"mlockall",
	/* 153 */	"munlockall",
	/* 154 */	"sched_setparam",
	/* 155 */	"sched_getparam",
	/* 156 */	"sched_setscheduler",
	/* 157 */	"sched_getscheduler",
	/* 158 */	"sched_yield",
	/* 159 */	"sched_get_priority_max",
	/* 160 */	"sched_get_priority_min",
	/* 161 */	"#161 (unimplemented sched_rr_get_interval)",
	/* 162 */	"nanosleep",
	/* 163 */	"mremap",
	/* 164 */	"setresuid16",
	/* 165 */	"getresuid16",
	/* 166 */	"#166 (unimplemented vm86)",
	/* 167 */	"#167 (unimplemented query_module)",
	/* 168 */	"poll",
	/* 169 */	"#169 (unimplemented nfsservctl)",
	/* 170 */	"setresgid16",
	/* 171 */	"getresgid16",
	/* 172 */	"#172 (unimplemented prctl)",
	/* 173 */	"rt_sigreturn",
	/* 174 */	"rt_sigaction",
	/* 175 */	"rt_sigprocmask",
	/* 176 */	"rt_sigpending",
	/* 177 */	"rt_sigtimedwait",
	/* 178 */	"rt_queueinfo",
	/* 179 */	"rt_sigsuspend",
	/* 180 */	"pread",
	/* 181 */	"pwrite",
	/* 182 */	"lchown16",
	/* 183 */	"__getcwd",
	/* 184 */	"#184 (unimplemented capget)",
	/* 185 */	"#185 (unimplemented capset)",
	/* 186 */	"sigaltstack",
	/* 187 */	"#187 (unimplemented sendfile)",
	/* 188 */	"#188 (unimplemented getpmsg)",
	/* 189 */	"#189 (unimplemented putpmsg)",
	/* 190 */	"__vfork14",
	/* 191 */	"ugetrlimit",
#define linux_sys_mmap2_args linux_sys_mmap_args
	/* 192 */	"mmap2",
	/* 193 */	"truncate64",
	/* 194 */	"ftruncate64",
	/* 195 */	"stat64",
	/* 196 */	"lstat64",
	/* 197 */	"fstat64",
	/* 198 */	"__posix_chown",
	/* 199 */	"getuid",
	/* 200 */	"getgid",
	/* 201 */	"geteuid",
	/* 202 */	"getegid",
	/* 203 */	"setreuid",
	/* 204 */	"setregid",
	/* 205 */	"getgroups",
	/* 206 */	"setgroups",
	/* 207 */	"__posix_fchown",
	/* 208 */	"setresuid",
	/* 209 */	"getresuid",
	/* 210 */	"setresgid",
	/* 211 */	"getresgid",
	/* 212 */	"__posix_lchown",
	/* 213 */	"setuid",
	/* 214 */	"setgid",
	/* 215 */	"setfsuid",
	/* 216 */	"setfsgid",
	/* 217 */	"#217 (unimplemented / * unused * /)",
	/* 218 */	"#218 (unimplemented / * unused * /)",
	/* 219 */	"#219 (unimplemented / * unused * /)",
	/* 220 */	"getdents64",
	/* 221 */	"gettid",
	/* 222 */	"tkill",
	/* 223 */	"setxattr",
	/* 224 */	"lsetxattr",
	/* 225 */	"fsetxattr",
	/* 226 */	"getxattr",
	/* 227 */	"lgetxattr",
	/* 228 */	"fgetxattr",
	/* 229 */	"listxattr",
	/* 230 */	"llistxattr",
	/* 231 */	"flistxattr",
	/* 232 */	"removexattr",
	/* 233 */	"lremovexattr",
	/* 234 */	"fremovexattr",
	/* 235 */	"futex",
	/* 236 */	"#236 (unimplemented sendfile64)",
	/* 237 */	"mincore",
	/* 238 */	"madvise",
	/* 239 */	"fcntl64",
	/* 240 */	"#240 (unimplemented readahead)",
	/* 241 */	"#241 (unimplemented io_setup)",
	/* 242 */	"#242 (unimplemented io_destroy)",
	/* 243 */	"#243 (unimplemented io_getevents)",
	/* 244 */	"#244 (unimplemented io_submit)",
	/* 245 */	"#245 (unimplemented io_cancel)",
	/* 246 */	"fadvise64",
	/* 247 */	"#247 (unimplemented exit_group)",
	/* 248 */	"#248 (unimplemented lookup_dcookie)",
	/* 249 */	"#249 (unimplemented epoll_create)",
	/* 250 */	"#250 (unimplemented epoll_ctl)",
	/* 251 */	"#251 (unimplemented epoll_wait)",
	/* 252 */	"#252 (unimplemented remap_file_pages)",
	/* 253 */	"set_tid_address",
	/* 254 */	"#254 (unimplemented timer_create)",
	/* 255 */	"#255 (unimplemented timer_settime)",
	/* 256 */	"#256 (unimplemented timer_gettime)",
	/* 257 */	"#257 (unimplemented timer_getoverrun)",
	/* 258 */	"#258 (unimplemented timer_ delete)",
	/* 259 */	"clock_settime",
	/* 260 */	"clock_gettime",
	/* 261 */	"clock_getres",
	/* 262 */	"clock_nanosleep",
	/* 263 */	"statfs64",
	/* 264 */	"fstatfs64",
	/* 265 */	"tgkill",
	/* 266 */	"utimes",
	/* 267 */	"fadvise64_64",
	/* 268 */	"#268 (unimplemented mbind)",
	/* 269 */	"#269 (unimplemented get_mempolicy)",
	/* 270 */	"#270 (unimplemented set_mempolicy)",
	/* 271 */	"#271 (unimplemented mq_open)",
	/* 272 */	"#272 (unimplemented mq_unlink)",
	/* 273 */	"#273 (unimplemented mq_timedsend)",
	/* 274 */	"#274 (unimplemented mq_timedreceive)",
	/* 275 */	"#275 (unimplemented mq_notify)",
	/* 276 */	"#276 (unimplemented mq_getsetattr)",
	/* 277 */	"#277 (unimplemented waitid)",
	/* 278 */	"#278 (unimplemented vserver)",
	/* 279 */	"#279 (unimplemented add_key)",
	/* 280 */	"#280 (unimplemented request_key)",
	/* 281 */	"#281 (unimplemented keyctl)",
	/* 282 */	"#282 (unimplemented ioprio_set)",
	/* 283 */	"#283 (unimplemented ioprio_get)",
	/* 284 */	"#284 (unimplemented inotify_init)",
	/* 285 */	"#285 (unimplemented inotify_add_watch)",
	/* 286 */	"#286 (unimplemented inotify_rm_watch)",
	/* 287 */	"#287 (unimplemented migrate_pages)",
	/* 288 */	"openat",
	/* 289 */	"mkdirat",
	/* 290 */	"mknodat",
	/* 291 */	"fchownat",
	/* 292 */	"#292 (unimplemented futimesat)",
	/* 293 */	"fstatat64",
	/* 294 */	"unlinkat",
	/* 295 */	"renameat",
	/* 296 */	"linkat",
	/* 297 */	"symlinkat",
	/* 298 */	"readlinkat",
	/* 299 */	"fchmodat",
	/* 300 */	"faccessat",
	/* 301 */	"#301 (unimplemented pselect6)",
	/* 302 */	"ppoll",
	/* 303 */	"#303 (unimplemented unshare)",
	/* 304 */	"set_robust_list",
	/* 305 */	"get_robust_list",
	/* 306 */	"#306 (unimplemented splice)",
	/* 307 */	"#307 (unimplemented sync_file_range)",
	/* 308 */	"#308 (unimplemented tee)",
	/* 309 */	"#309 (unimplemented vmsplice)",
	/* 310 */	"#310 (unimplemented move_pages)",
	/* 311 */	"sched_setaffinity",
	/* 312 */	"sched_getaffinity",
	/* 313 */	"#313 (unimplemented kexec_load)",
	/* 314 */	"#314 (unimplemented getcpu)",
	/* 315 */	"#315 (unimplemented epoll_wait)",
	/* 316 */	"utimensat",
	/* 317 */	"#317 (unimplemented signalfd)",
	/* 318 */	"#318 (unimplemented timerfd_create)",
	/* 319 */	"#319 (unimplemented eventfd)",
	/* 320 */	"#320 (unimplemented fallocate)",
	/* 321 */	"#321 (unimplemented timerfd_settime)",
	/* 322 */	"#322 (unimplemented timerfd_gettime)",
	/* 323 */	"#323 (unimplemented signalfd4)",
	/* 324 */	"#324 (unimplemented eventfd2)",
	/* 325 */	"#325 (unimplemented epoll_create1)",
	/* 326 */	"dup3",
	/* 327 */	"pipe2",
	/* 328 */	"#328 (unimplemented inotify_init1)",
	/* 329 */	"#329 (unimplemented preadv)",
	/* 330 */	"#330 (unimplemented pwritev)",
	/* 331 */	"#331 (unimplemented rt_tgsigqueueinfo)",
	/* 332 */	"#332 (unimplemented perf_counter_open)",
	/* 333 */	"#333 (unimplemented set_thread_area)",
	/* 334 */	"#334 (unimplemented get_thread_area)",
	/* 335 */	"#335 (unimplemented atomic_cmpxchg_32)",
	/* 336 */	"#336 (unimplemented atomic_barrier)",
	/* 337 */	"# filler",
	/* 338 */	"# filler",
	/* 339 */	"# filler",
	/* 340 */	"# filler",
	/* 341 */	"# filler",
	/* 342 */	"# filler",
	/* 343 */	"# filler",
	/* 344 */	"# filler",
	/* 345 */	"# filler",
	/* 346 */	"# filler",
	/* 347 */	"# filler",
	/* 348 */	"# filler",
	/* 349 */	"# filler",
	/* 350 */	"# filler",
	/* 351 */	"# filler",
	/* 352 */	"# filler",
	/* 353 */	"# filler",
	/* 354 */	"# filler",
	/* 355 */	"# filler",
	/* 356 */	"# filler",
	/* 357 */	"# filler",
	/* 358 */	"# filler",
	/* 359 */	"# filler",
	/* 360 */	"# filler",
	/* 361 */	"# filler",
	/* 362 */	"# filler",
	/* 363 */	"# filler",
	/* 364 */	"# filler",
	/* 365 */	"# filler",
	/* 366 */	"# filler",
	/* 367 */	"# filler",
	/* 368 */	"# filler",
	/* 369 */	"# filler",
	/* 370 */	"# filler",
	/* 371 */	"# filler",
	/* 372 */	"# filler",
	/* 373 */	"# filler",
	/* 374 */	"# filler",
	/* 375 */	"# filler",
	/* 376 */	"# filler",
	/* 377 */	"# filler",
	/* 378 */	"# filler",
	/* 379 */	"# filler",
	/* 380 */	"# filler",
	/* 381 */	"# filler",
	/* 382 */	"# filler",
	/* 383 */	"# filler",
	/* 384 */	"# filler",
	/* 385 */	"# filler",
	/* 386 */	"# filler",
	/* 387 */	"# filler",
	/* 388 */	"# filler",
	/* 389 */	"# filler",
	/* 390 */	"# filler",
	/* 391 */	"# filler",
	/* 392 */	"# filler",
	/* 393 */	"# filler",
	/* 394 */	"# filler",
	/* 395 */	"# filler",
	/* 396 */	"# filler",
	/* 397 */	"# filler",
	/* 398 */	"# filler",
	/* 399 */	"# filler",
	/* 400 */	"# filler",
	/* 401 */	"# filler",
	/* 402 */	"# filler",
	/* 403 */	"# filler",
	/* 404 */	"# filler",
	/* 405 */	"# filler",
	/* 406 */	"# filler",
	/* 407 */	"# filler",
	/* 408 */	"# filler",
	/* 409 */	"# filler",
	/* 410 */	"# filler",
	/* 411 */	"# filler",
	/* 412 */	"# filler",
	/* 413 */	"# filler",
	/* 414 */	"# filler",
	/* 415 */	"# filler",
	/* 416 */	"# filler",
	/* 417 */	"# filler",
	/* 418 */	"# filler",
	/* 419 */	"# filler",
	/* 420 */	"# filler",
	/* 421 */	"# filler",
	/* 422 */	"# filler",
	/* 423 */	"# filler",
	/* 424 */	"# filler",
	/* 425 */	"# filler",
	/* 426 */	"# filler",
	/* 427 */	"# filler",
	/* 428 */	"# filler",
	/* 429 */	"# filler",
	/* 430 */	"# filler",
	/* 431 */	"# filler",
	/* 432 */	"# filler",
	/* 433 */	"# filler",
	/* 434 */	"# filler",
	/* 435 */	"# filler",
	/* 436 */	"# filler",
	/* 437 */	"# filler",
	/* 438 */	"# filler",
	/* 439 */	"# filler",
	/* 440 */	"# filler",
	/* 441 */	"# filler",
	/* 442 */	"# filler",
	/* 443 */	"# filler",
	/* 444 */	"# filler",
	/* 445 */	"# filler",
	/* 446 */	"# filler",
	/* 447 */	"# filler",
	/* 448 */	"# filler",
	/* 449 */	"# filler",
	/* 450 */	"# filler",
	/* 451 */	"# filler",
	/* 452 */	"# filler",
	/* 453 */	"# filler",
	/* 454 */	"# filler",
	/* 455 */	"# filler",
	/* 456 */	"# filler",
	/* 457 */	"# filler",
	/* 458 */	"# filler",
	/* 459 */	"# filler",
	/* 460 */	"# filler",
	/* 461 */	"# filler",
	/* 462 */	"# filler",
	/* 463 */	"# filler",
	/* 464 */	"# filler",
	/* 465 */	"# filler",
	/* 466 */	"# filler",
	/* 467 */	"# filler",
	/* 468 */	"# filler",
	/* 469 */	"# filler",
	/* 470 */	"# filler",
	/* 471 */	"# filler",
	/* 472 */	"# filler",
	/* 473 */	"# filler",
	/* 474 */	"# filler",
	/* 475 */	"# filler",
	/* 476 */	"# filler",
	/* 477 */	"# filler",
	/* 478 */	"# filler",
	/* 479 */	"# filler",
	/* 480 */	"# filler",
	/* 481 */	"# filler",
	/* 482 */	"# filler",
	/* 483 */	"# filler",
	/* 484 */	"# filler",
	/* 485 */	"# filler",
	/* 486 */	"# filler",
	/* 487 */	"# filler",
	/* 488 */	"# filler",
	/* 489 */	"# filler",
	/* 490 */	"# filler",
	/* 491 */	"# filler",
	/* 492 */	"# filler",
	/* 493 */	"# filler",
	/* 494 */	"# filler",
	/* 495 */	"# filler",
	/* 496 */	"# filler",
	/* 497 */	"# filler",
	/* 498 */	"# filler",
	/* 499 */	"# filler",
	/* 500 */	"# filler",
	/* 501 */	"# filler",
	/* 502 */	"# filler",
	/* 503 */	"# filler",
	/* 504 */	"# filler",
	/* 505 */	"# filler",
	/* 506 */	"# filler",
	/* 507 */	"# filler",
	/* 508 */	"# filler",
	/* 509 */	"# filler",
	/* 510 */	"# filler",
	/* 511 */	"# filler",
};
