# $NetBSD$

# hash functions
.PATH: ${.CURDIR}/hash/rmd160

SRCS+=	rmd160.c rmd160hl.c

MAN+=	rmd160.3

MLINKS+=rmd160.3 RMD160Init.3    rmd160.3 RMD160Update.3
MLINKS+=rmd160.3 RMD160Final.3   rmd160.3 RMD160Transform.3
MLINKS+=rmd160.3 RMD160End.3     rmd160.3 RMD160File.3
MLINKS+=rmd160.3 RMD160Data.3
