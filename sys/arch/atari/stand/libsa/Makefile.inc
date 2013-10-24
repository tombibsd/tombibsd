# $NetBSD$

.PATH.c: ${SA_EXTRADIR}
.PATH.S: ${SA_EXTRADIR}

# NetBSD/atari specific replacements: dev.c

# machine dependent routines
SRCS+=   consio.S dev.c diskio.c
