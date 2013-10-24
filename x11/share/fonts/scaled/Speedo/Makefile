#	$NetBSD$

.include <bsd.own.mk>

FONTSUBDIR=	Speedo

FILES=		font0648.spd font0649.spd font0709.spd font0710.spd \
        	font0419.spd font0582.spd font0583.spd font0611.spd

# we bring our own
FILES+=		fonts.scale
create.fonts.scale:
	# already there

.include "../Makefile.scaled"

.include <bsd.x11.mk>
.include <bsd.prog.mk>
