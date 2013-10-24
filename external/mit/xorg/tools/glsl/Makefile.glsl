#	$NetBSD$

GLSLDIR!=	cd ${NETBSDSRCDIR}/external/mit/xorg/tools/glsl && ${PRINTOBJDIR}
GLSL=	${GLSLDIR}/glsl-compile

${GLSL}:
	(cd ${NETBSDSRCDIR}/external/mit/xorg/tools/glsl && ${MAKE})
