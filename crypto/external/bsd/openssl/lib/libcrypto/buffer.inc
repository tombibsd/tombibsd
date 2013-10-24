#	$NetBSD$
#
#	@(#) Copyright (c) 1995 Simon J. Gerraty
#
#	SRCS extracted from src/crypto/dist/openssl/crypto/buffer/Makefile
#

.PATH:	${OPENSSLSRC}/crypto/buffer


BUFFER_SRCS = buffer.c buf_err.c buf_str.c
SRCS += ${BUFFER_SRCS}

.for cryptosrc in ${BUFFER_SRCS}
CPPFLAGS.${cryptosrc} = -I${OPENSSLSRC}/crypto/buffer
.endfor
