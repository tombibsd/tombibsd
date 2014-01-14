#	$NetBSD$

LIB=	lldReaderWriterMachO

.include <bsd.init.mk>

.PATH: ${LLD_SRCDIR}/lib/ReaderWriter/MachO

SRCS+=	MachOLinkingContext.cpp \
	MachONormalizedFileBinaryReader.cpp \
	MachONormalizedFileBinaryWriter.cpp \
	MachONormalizedFileFromAtoms.cpp \
	MachONormalizedFileYAML.cpp \
	ReferenceKinds.cpp \
	WriterMachO.cpp

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
