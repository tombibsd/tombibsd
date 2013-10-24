#	$NetBSD$
#
#	@(#) Copyright (c) 1995 Simon J. Gerraty
#
#	SRCS extracted from src/crypto/dist/openssl/crypto/ripemd/Makefile
#

.PATH:	${OPENSSLSRC}/crypto/ripemd


RIPEMD_SRCS = rmd_dgst.c rmd_one.c
SRCS += ${RIPEMD_SRCS}

.for cryptosrc in ${RIPEMD_SRCS}
CPPFLAGS.${cryptosrc} = -I${OPENSSLSRC}/crypto/ripemd
.endfor
