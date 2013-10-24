#$NetBSD$

.include "../../Makefile.inc"

S!=             cd ${.CURDIR}/../../..;pwd
.PATH:	${S}/dev/dm

CPPFLAGS += -DDM_TARGET_MODULE
KMOD=	dm_target_zero
SRCS=   dm_target_zero.c

.include <bsd.kmodule.mk>
