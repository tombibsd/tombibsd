#	$NetBSD$

NOOBJ=	# defined

.include <bsd.own.mk>

SUBDIR= client server

.if ${MKSHARE} != "no" && ${MKCRYPTO} != "no"
FILES=	README
FILESDIR=/usr/share/examples/racoon/roadwarrior
.endif

DIST= ${NETBSDSRCDIR}/crypto/dist/ipsec-tools
.PATH:	${DIST}/src/racoon/samples/roadwarrior

.include <bsd.prog.mk>
.include <bsd.subdir.mk>
