# $NetBSD$

.include <bsd.own.mk>

# XXX catpages conflicts with the corresponding phony target name
CONFIGFILES.etc=\
		atf \
		bluetooth \
		./catpages \
		daily \
		ddbonpanic \
		defaults \
		dhcpcd \
		dhcpcdrundir \
		envsys \
		gid \
		gpio \
		hosts \
		./install \
		iscsi \
		mailerconf \
		makedev \
		monthly \
		motd \
		mtree \
		named \
		obsolete \
		pam \
		periodic \
		pf \
		ptyfsoldnodes \
		pwd_mkdb \
		rc \
		security \
		sendmail \
		ssh \
		tcpdumpchroot \
		uid \
		varrwho \
		varshm \
		weekly \
		wscons
.if ${MKX11} != "no"
CONFIGFILES.xetc=\
		fontconfig \
		x11 \
		xkb
.endif
CONFIGFILES=	${CONFIGFILES.etc} ${CONFIGFILES.xetc}

FILESDIR=	/etc/install.d
FILESMODE=	${NONBINMODE}

.include <bsd.prog.mk>
