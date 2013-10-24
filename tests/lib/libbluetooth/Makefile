#	$NetBSD$

.include <bsd.own.mk>

TESTSDIR=	${TESTSBASE}/lib/libbluetooth

DPADD+=		${LIBBLUETOOTH}
LDADD+=		-lbluetooth

TESTS_C+=	t_bluetooth
TESTS_C+=	t_sdp_data
TESTS_C+=	t_sdp_get
TESTS_C+=	t_sdp_match
TESTS_C+=	t_sdp_put
TESTS_C+=	t_sdp_set

.include <bsd.test.mk>
