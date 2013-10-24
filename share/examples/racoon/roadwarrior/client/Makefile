#	$NetBSD$

NOOBJ=	# defined

.include <bsd.own.mk>

.if ${MKSHARE} != "no" && ${MKCRYPTO} != "no"
FILES=	phase1-down.sh phase1-up.sh racoon.conf
FILESDIR=/usr/share/examples/racoon/roadwarrior/client
.endif

DIST= ${NETBSDSRCDIR}/crypto/dist/ipsec-tools
.PATH:	${DIST}/src/racoon/samples/roadwarrior/client

.include <bsd.prog.mk>
