#	$NetBSD$

# makefile fragment for mesa src/loader

# loader stuff.
.PATH:		${X11SRCDIR.MesaLib}/src/loader
.PATH:		${X11SRCDIR.MesaLib}/src/mesa/drivers/dri/common
SRCS.loader += \
	loader.c \
	pci_id_driver_map.c \
	xmlconfig.c

.for _f in ${SRCS.loader}
CPPFLAGS.${_f}= 	-I${X11SRCDIR.MesaLib}/src/mesa \
			-I${X11SRCDIR.MesaLib}/src
.endfor

SRCS+=	${SRCS.loader}
