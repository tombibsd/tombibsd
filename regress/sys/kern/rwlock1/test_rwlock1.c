/*	$NetBSD$	*/

/*-
 * Copyright (c) 2007, 2008 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Andrew Doran.
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

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/kthread.h>
#include <sys/kernel.h>

#define	NTHREADS	32
#define	SECONDS		60

int	testcall(struct lwp *, void *, register_t *);
void	thread1(void *);
void	thread_exit(void);

lwp_t		*test_threads[NTHREADS];
kmutex_t	test_mutex;
krwlock_t	test_rwlock;
kcondvar_t	test_cv;
int		test_count;
int		test_exit;

static int primes[NTHREADS] = {
	 17,  19,  23,  29,
	 31,  37,  41,  43,
	 47,  53,  59,  61,
	 67,  71,  73,  79,
	 83,  89,  97, 101,
	103, 107, 109, 113,
	127, 131, 137, 139,
	149, 151, 157, 163,
};

void
thread_exit(void)
{

	mutex_enter(&test_mutex);
	if (--test_count == 0)
		cv_signal(&test_cv);
	mutex_exit(&test_mutex);
	kthread_exit(0);
}

void
thread1(void *cookie)
{
	int count;
	krw_t op;

	for (count = 0; !test_exit; count++) {
		if (count % *(int *)cookie == 0)
			op = RW_WRITER;
		else
			op = RW_READER;
		rw_enter(&test_rwlock, op);
		if ((arc4random() % 11) == 0)
			yield();
		rw_exit(&test_rwlock);
		if ((arc4random() % 23) == 0)
			yield();
	}

	thread_exit();
}

int
testcall(struct lwp *l, void *uap, register_t *retval)
{
	int i;

	mutex_init(&test_mutex, MUTEX_DEFAULT, IPL_NONE);
	rw_init(&test_rwlock);
	cv_init(&test_cv, "testcv");

	printf("test: creating threads\n");

	test_count = NTHREADS;
	test_exit = 0;

	for (i = 0; i < test_count; i++)
		kthread_create(0, KTHREAD_MPSAFE, NULL, thread1, &primes[i],
		    &test_threads[i], "thread%d", i);

	printf("test: sleeping\n");

	mutex_enter(&test_mutex);
	while (test_count != 0) {
		(void)cv_timedwait(&test_cv, &test_mutex, hz * SECONDS);
		test_exit = 1;
	}
	mutex_exit(&test_mutex);

	printf("test: finished\n");

	cv_destroy(&test_cv);
	rw_destroy(&test_rwlock);
	mutex_destroy(&test_mutex);

	return 0;
}
