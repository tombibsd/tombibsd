#	$NetBSD$

.include <bsd.own.mk>

SSHDIST?= ${NETBSDSRCDIR}/crypto/external/bsd/openssh/dist

SUBDIR=	ssh sshd ssh-add ssh-keygen ssh-agent scp sftp-server \
	ssh-keysign ssh-keyscan sftp ssh-pkcs11-helper

.PATH: ${SSHDIST}
.MADE: moduli
CONFIGFILES=	ssh_config sshd_config moduli
FILESDIR=	/etc/ssh
FILESDIR_moduli=/etc

.include <bsd.files.mk>
.include <bsd.subdir.mk>
