#	$NetBSD$

.include <bsd.endian.mk>

.if empty(MACHINE_ARCH:Mearm*) && ${TARGET_ENDIANNESS} == "1234"

SUBDIR= boot32 nbfs

.endif

.include <bsd.subdir.mk>
