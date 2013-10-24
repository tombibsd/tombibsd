# $NetBSD$

PROG            =       dtmfdecode
SRC             =       dtmfdecode.c

# libm is only necessary if USE_COS is defined in the source
#LDADD		+=	-lm

UUDECODE_FILES	=	dtmfsounds.al

test:	${PROG} ${UUDECODE_FILES}
	./${PROG} < dtmfsounds.al

.include <bsd.files.mk>
.include <bsd.prog.mk>
