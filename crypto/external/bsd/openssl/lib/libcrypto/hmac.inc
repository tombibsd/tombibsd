#	$NetBSD$
#
#	@(#) Copyright (c) 1995 Simon J. Gerraty
#
#	SRCS extracted from src/crypto/dist/openssl/crypto/hmac/Makefile
#

.PATH:	${OPENSSLSRC}/crypto/hmac


HMAC_SRCS = hmac.c hm_ameth.c hm_pmeth.c
SRCS += ${HMAC_SRCS}

.for cryptosrc in ${HMAC_SRCS}
CPPFLAGS.${cryptosrc} = -I${OPENSSLSRC}/crypto/hmac
.endfor
