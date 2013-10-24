# $NetBSD$

TOPDIR=		${NETBSDSRCDIR}/external/bsd/atf
SRCDIR=		${TOPDIR}/dist

ATF_VERSION!=	grep 'define VERSION' ${TOPDIR}/lib/libatf-c/bconfig.h \
		| cut -d '"' -f 2
