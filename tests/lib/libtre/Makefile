#	$NetBSD$

LDADD+=-ltre
DPADD+=${LIBTRE}
TESTSDIR=       ${TESTSBASE}/lib/libtre
# XXX: tre eats copious amounts of memory even 9 does not work
IMPLEMENTATION=-DREGEX_TRE -DREGEX_MAXSIZE=2 -DSKIP_RIGHTASSOC

# Remove the following 2 lines once the standard tests have been fixed.
PROGS=
TESTS_SH=

LCREGEX=${.CURDIR}/../libc/regex
.PATH: ${LCREGEX}
.include "${LCREGEX}/Makefile"

