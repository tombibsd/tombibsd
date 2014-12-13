#	$NetBSD$
#

GNUHOSTDIST=	${.CURDIR}/../../external/gpl2/gmake/dist

CONFIGURE_ENV+=	CC=${HOST_CC:Q} \
		CFLAGS=${HOST_CFLAGS:Q} \
		CPPFLAGS=${HOST_CPPFLAGS:Q} \
		CXX=${HOST_CXX:Q}

CONFIGURE_ARGS=	--program-prefix=${_TOOL_PREFIX}g
CONFIGURE_ARGS+=--disable-nls

MAKE_ARGS=	MAKEINFO=${TOOL_MAKEINFO:Q}

.NOTPARALLEL:

.include "${.CURDIR}/../Makefile.gnuhost"
