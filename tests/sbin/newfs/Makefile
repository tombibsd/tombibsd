# $NetBSD$

.include <bsd.own.mk>

TESTSDIR=	${TESTSBASE}/sbin/newfs

.for name in t_enable_quotas
TESTS_SH+=	${name}
TESTS_SH_SRC_${name}=	quotas_common.sh ${name}.sh
.endfor

.include <bsd.test.mk>
