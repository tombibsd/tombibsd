.\"	$NetBSD$
.\"
.\" Copyright (c) 1983, 1993, 1994
.\"	The Regents of the University of California.  All rights reserved.
.\"
.\" Redistribution and use in source and binary forms, with or without
.\" modification, are permitted provided that the following conditions
.\" are met:
.\" 1. Redistributions of source code must retain the above copyright
.\"    notice, this list of conditions and the following disclaimer.
.\" 2. Redistributions in binary form must reproduce the above copyright
.\"    notice, this list of conditions and the following disclaimer in the
.\"    documentation and/or other materials provided with the distribution.
.\" 3. Neither the name of the University nor the names of its contributors
.\"    may be used to endorse or promote products derived from this software
.\"    without specific prior written permission.
.\"
.\" THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
.\" ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
.\" IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
.\" ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
.\" FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
.\" DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
.\" OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
.\" HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
.\" LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
.\" OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
.\" SUCH DAMAGE.
.\"
.\"	@(#)1.3.t	8.6 (Berkeley) 5/29/94
.\"
.Sh 2 11 "Signals
.PP
.Sh 3 11 "Overview
.PP
The system defines a set of \fIsignals\fP that may be delivered
to a process.  Signal delivery resembles the occurrence of a hardware
interrupt: the signal is blocked from further occurrence,
the current process context is saved, and a new one
is built.
A process may specify a \fIhandler\fP to which a signal is delivered,
or specify that the signal is to be \fIblocked\fP or \fIignored\fP.
A process may also specify that a
\fIdefault\fP action is to be taken when signals occur.
.PP
Some signals will cause a process to exit if they are not caught.
This may be accompanied by creation of a \fIcore\fP image file,
containing
the current memory image of the process for use in post-mortem debugging.
A process may also choose to have signals delivered on a special stack,
so that sophisticated software stack manipulations are possible.
.PP
All signals have the same \fIpriority\fP.
If multiple signals are pending,
signals that may be generated by the
program's action are delivered first; the order in which other signals
are delivered to a process is not specified.
Signal routines execute
with the signal that caused their invocation \fIblocked\fP, but other
signals may occur.
Multiple signals may be delivered on a single entry to the system,
as if signal handlers were interrupted by other signal handlers.
Mechanisms are provided whereby critical sections
of code may protect themselves against the occurrence of specified signals.
.Sh 3 11 "Signal types
.PP
The signals defined by the system fall into one of
five classes: hardware conditions,
software conditions, input/output notification, process control, or
resource control.
The set of signals is defined by the file \fI<signal.h>\fP.
.PP
Hardware signals are derived from exceptional conditions which
may occur during
execution.  Such signals include SIGFPE representing floating
point and other arithmetic exceptions, SIGILL for illegal instruction
execution, SIGSEGV for attempts to access addresses outside the
currently assigned area of memory,
and SIGBUS for accesses that violate memory access constraints.
.PP
Software signals reflect interrupts generated by user request:
SIGINT for the normal interrupt signal; SIGQUIT for the more
powerful \fIquit\fP signal, which normally causes a core image
to be generated; SIGHUP and SIGTERM that cause graceful
process termination, either because a user has ``hung up'', or
by user or program request; and SIGKILL, a more powerful termination
signal which a process cannot catch or ignore.
Programs may define their own asynchronous events using SIGUSR1
and SIGUSR2.
Other software signals (SIGALRM, SIGVTALRM, SIGPROF)
indicate the expiration of interval timers.
When a window changes size, a SIGWINCH is sent to the
controlling terminal process group.
.PP
A process can request notification via a SIGIO signal
when input or output is possible
on a descriptor, or when a \fInon-blocking\fP operation completes.
A process may request to receive a SIGURG signal when an
urgent condition arises. 
.PP
A process may be \fIstopped\fP by a signal sent to it or the members
of its process group.  The SIGSTOP signal is a powerful stop
signal, because it cannot be caught.  Other stop signals
SIGTSTP, SIGTTIN, and SIGTTOU are used when a user request, input
request, or output request respectively is the reason for stopping the process.
A SIGCONT signal is sent to a process when it is
continued from a stopped state.
Processes may receive notification with a SIGCHLD signal when
a child process changes state, either by stopping or by terminating.
.PP
Exceeding resource limits may cause signals to be generated.
SIGXCPU occurs when a process nears its CPU time limit and
SIGXFSZ when a process reaches the limit on file size.
.Sh 3 12 "Signal handlers
.PP
A process has a handler associated with each signal.
The handler controls the way the signal is delivered.
The call:
.DS
.TS
l s s
l l l.
struct sigaction {
	void	(*sa_handler)();
	sigset_t	sa_mask;
	int	sa_flags;
};
.TE
.DE
.DS
.Fd sigaction 3 "setup software signal handler
sigaction(signo, sa, osa);
int signo; struct sigaction *sa; result struct sigaction *osa;
.DE
assigns interrupt handler address \fIsa_handler\fP to signal \fIsigno\fP.
Each handler address
specifies either an interrupt routine for the signal, that the
signal is to be ignored,
or that a default action (usually process termination) is to occur
if the signal occurs.
The constants
SIG_IGN and SIG_DFL used as values for \fIsa_handler\fP
cause ignoring or defaulting of a condition, respectively.
The \fIsa_mask\fP value specifies the
signal mask to be used when the handler is invoked; it implicitly includes
the signal which invoked the handler.
Signal masks include one bit for each signal.
The following macros, defined in \fIsignal.h\fP,
create an empty mask, then put \fIsigno\fP into it:
.DS
sigemptyset(set);
sigaddset(set, signo);
result sigset_t *set; int signo;
.DE
\fISa_flags\fP specifies whether pending system calls should be
restarted if the signal handler returns (SA_RESTART) and
whether the handler should operate on the normal run-time
stack or a special signal stack (SA_ONSTACK; see below).
If \fIosa\fP is non-zero, the previous signal handler information is returned.
.PP
When a signal condition arises for a process, the signal
is added to a set of signals pending for the process.
If the signal is not currently \fIblocked\fP by the process
it then will be delivered.
The process of signal delivery adds the signal to be delivered
and those signals specified in the associated signal
handler's \fIsa_mask\fP to a set of those \fImasked\fP
for the process, saves the current process context,
and places the process in the context of the signal
handling routine.  The call is arranged so that if the signal
handling routine returns normally, the signal mask will be restored
and the process will resume execution in the original context.
.PP
The mask of \fIblocked\fP signals is independent of handlers for
signals.  It delays signals from being delivered much as a
raised hardware interrupt priority level delays hardware interrupts.
Preventing an interrupt from occurring by changing the handler is analogous to
disabling a device from further interrupts.
.LP
The signal handling routine \fIsa_handler\fP is called by a C call
of the form:
.DS
(*sa_handler)(signo, code, scp);
int signo; long code; struct sigcontext *scp;
.DE
The \fIsigno\fP gives the number of the signal that occurred, and
the \fIcode\fP, a word of signal-specific information supplied by the hardware.
The \fIscp\fP parameter is a pointer to a machine-dependent
structure containing the information for restoring the
context before the signal.
Normally this context will be restored when the signal handler returns.
However, a process may do so at any time by using the call:
.DS
.Fd sigreturn 1 "return from a signal
sigreturn(scp);
struct sigcontext *scp;
.DE
If the signal handler makes a call to
.Fn longjmp ,
the signal mask at the time of the corresponding
.Fn setjmp
is restored.
.Sh 3 13 "Sending signals
.LP
A process can send a signal to another process or processes group
with the call:
.DS
.Fd kill 2 "send signal to a process
kill(pid, signo)
pid_t pid; int signo;
.DE
For compatibility with old systems,
a compatibility routine is provided to send a signal to a process group:
.DS
.Fd killpg 2 "send signal to a process group
killpg(pgrp, signo)
pid_t pgrp; int signo;
.DE
Unless the process sending the signal is privileged,
it must have the same effective user id as the process receiving the signal.
.PP
Signals also are sent implicitly from a terminal device to the
process group associated with the terminal when certain input characters
are typed.
.Sh 3 13 "Protecting critical sections
.LP
The
.Fn sigprocmask
system call is used to manipulate the mask of blocked signals:
.DS
.Fd sigprocmask 3 "manipulate current signal mask
sigprocmask(how, newmask, oldmask);
int how; sigset_t *newmask; result sigset_t *oldmask;
.DE
The actions done by
.Fn sigprocmask
are to add to the list of masked signals (SIG_BLOCK),
delete from the list of masked signals (SIG_UNBLOCK),
and block a specific set of signals (SIG_SETMASK).
The
.Fn sigprocmask
call can be used to read the current mask
by specifying SIG_BLOCK with an empty \fInewmask\fP\|.
.PP
It is possible to check conditions with some signals blocked,
and then to pause waiting for a signal and restoring the mask, by using:
.DS
.Fd sigsuspend 1 "atomically release blocked signals and wait for interrupt
sigsuspend(mask);
sigset_t *mask;
.DE
It is also possible to find out which blocked signals
are pending delivery using the call:
.DS
.Fd sigpending 1 "get pending signals
sigpending(mask);
result sigset_t *mask;
.DE
.Sh 3 14 "Signal stacks
.LP
Applications that maintain complex or fixed size stacks can use
the call:
.DS
.TS
l s s
l l l.
struct sigaltstack {
	caddr_t	ss_sp;
	long	ss_size;
	int	ss_flags;
};
.TE
.DE
.DS
.Fd sigaltstack 2 "set and/or get signal stack context
sigaltstack(ss, oss)
struct sigaltstack *ss; result struct sigaltstack *oss;
.DE
to provide the system with a stack based at \fIss_sp\fP of size
\fIss_size\fP for delivery of signals.
The value \fIss_flags\fP indicates whether the
process is currently on the signal stack,
a notion maintained in software by the system.
.PP
When a signal is to be delivered to a handler for which the SA_ONSTACK
flag was set, the system checks whether
the process is on a signal stack.  If not, then the process is switched
to the signal stack for delivery,
with the return from the signal doing a
.Fn sigreturn
to restore the previous stack.
If the process takes a non-local exit from the signal routine,
.Fn longjmp
will do a
.Fn sigreturn
call to switch back to the run-time stack.
