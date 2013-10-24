#	$NetBSD$

#	$OpenBSD: Makefile.inc,v 1.4 1999/09/14 00:46:18 mickey Exp $

SRCS+=	bcmp.S bzero.S ffs.S

# NetBSD doesn't currently let archs supply a strlcpy.S.
# plus, the one that fredette made is untested.
#SRCS+=	strlcpy.S

