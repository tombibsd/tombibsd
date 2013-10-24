#	$NetBSD$

SUBDIR= libbug libsa .WAIT sboot netboot bootxx bootsd bootst \
	installboot

.ifmake !install
SUBDIR+= wrtvid
.endif

.include <bsd.subdir.mk>
