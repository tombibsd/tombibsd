# $NetBSD$

.include <bsd.own.mk>

TESTSDIR=	${TESTSBASE}/sbin/fsck_ffs

.for name in t_enable_quotas t_check_quotas
TESTS_SH+=	${name}
TESTS_SH_SRC_${name}=	quotas_common.sh ${name}.sh
.endfor

.include <bsd.test.mk>
