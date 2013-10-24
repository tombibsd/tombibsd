#$NetBSD$

.include "../../Makefile.inc"

S!=     cd ${.CURDIR}/../../..;pwd
.PATH:	${S}/dev/dm

CPPFLAGS += -DDM_TARGET_MODULE
KMOD=	dm_target_error
SRCS=   dm_target_error.c

.include <bsd.kmodule.mk>
