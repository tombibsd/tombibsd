#	$NetBSD$
#	from: @(#)Makefile	8.1 (Berkeley) 6/8/93

CONFIGFILES=	dot.cshrc dot.login dot.logout dot.profile dot.shrc
FILESDIR=	/etc/skel
.for F in ${CONFIGFILES}
FILESNAME_${F}=	${F:S/dot//}
.endfor

.include <bsd.prog.mk>
