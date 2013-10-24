# $NetBSD$

MODULE=	mach64

SRCS=	mach64_context.c mach64_ioctl.c mach64_screen.c mach64_span.c \
	mach64_state.c mach64_tex.c mach64_texmem.c mach64_texstate.c \
	mach64_tris.c mach64_vb.c mach64_dd.c mach64_lock.c

CWARNFLAGS.clang+=	-Wno-constant-logical-operand

.include "${.CURDIR}/../dri.mk"
