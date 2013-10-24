# $NetBSD$
#
# Build umount(8) without network support
#

SRCDIR=		${.CURDIR}/../../../sbin/umount

PROG=		umount
NOMAN=		# defined

CPPFLAGS+=	-DSMALL
WARNS?=		1

.include <bsd.prog.mk>

.PATH:		${SRCDIR}
