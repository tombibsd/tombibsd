# $NetBSD$

.ifndef _EXTERNAL_GPL3_GCC_LIB_LIBSTDCXX_MAKEFILE_INC_
_EXTERNAL_GPL3_GCC_LIB_LIBSTDCXX_MAKEFILE_INC_=1

GCC_MACHINE_ARCH=${MACHINE_ARCH:S/earmv5/earm/}

.include "../../Makefile.inc"
.sinclude "../../../Makefile.gcc_path"
.sinclude "../../../../Makefile.gcc_path"

.endif
