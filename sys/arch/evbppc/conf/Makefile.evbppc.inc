#	$NetBSD$

CPPFLAGS += -D__${BOARDTYPE}__

RAMDISKDIR!=	cd ${NETBSDSRCDIR}/distrib/${THISPPC:T}/ramdisk && ${PRINTOBJDIR}

.-include "${THISPPC}/conf/Makefile.${BOARDTYPE}.inc"
