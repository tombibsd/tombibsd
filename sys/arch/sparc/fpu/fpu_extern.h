/*	$NetBSD$	*/

/*-
 * Copyright (c) 1995 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Christos Zoulas.
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
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#if defined(_KERNEL_OPT)
#include "opt_sparc_arch.h"
#endif

struct proc;
#ifndef SUN4U
struct fpstate;
struct trapframe;
#else /* SUN4U */
struct fpstate64;
struct trapframe64;
#endif /* SUN4U */
union instr;
struct fpemu;
struct fpn;

/* fpu.c */
#ifndef SUN4U
int fpu_cleanup(struct lwp *, struct fpstate *);
int fpu_emulate(struct lwp *, struct trapframe *, struct fpstate *);
#else /* SUN4U */
int fpu_cleanup(struct lwp *, struct fpstate64 *);
int fpu_emulate(struct lwp *, struct trapframe64 *, struct fpstate64 *);
#endif /* SUN4U */
int fpu_execute(struct fpemu *, union instr);

/* fpu_add.c */
struct fpn *fpu_add(struct fpemu *);

/* fpu_compare.c */
void fpu_compare(struct fpemu *, int);

/* fpu_div.c */
struct fpn *fpu_div(struct fpemu *);

/* fpu_explode.c */
int fpu_itof(struct fpn *, u_int);
#ifdef SUN4U
int fpu_xtof(struct fpn *, uint64_t);
#endif /* SUN4U */
int fpu_stof(struct fpn *, u_int);
int fpu_dtof(struct fpn *, u_int, u_int );
int fpu_qtof(struct fpn *, u_int, u_int , u_int , u_int );
void fpu_explode(struct fpemu *, struct fpn *, int, int );

/* fpu_implode.c */
u_int fpu_ftoi(struct fpemu *, struct fpn *);
#ifdef SUN4U
u_int fpu_ftox(struct fpemu *, struct fpn *, u_int *);
#endif /* SUN4U */
u_int fpu_ftos(struct fpemu *, struct fpn *);
u_int fpu_ftod(struct fpemu *, struct fpn *, u_int *);
u_int fpu_ftoq(struct fpemu *, struct fpn *, u_int *);
void fpu_implode(struct fpemu *, struct fpn *, int, u_int *);

/* fpu_mul.c */
struct fpn *fpu_mul(struct fpemu *);

/* fpu_sqrt.c */
struct fpn *fpu_sqrt(struct fpemu *);

/* fpu_subr.c */
int fpu_shr(register struct fpn *, register int);
void fpu_norm(register struct fpn *);
struct fpn *fpu_newnan(register struct fpemu *);
