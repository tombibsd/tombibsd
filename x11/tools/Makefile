#	$NetBSD$

# These are used by the 'includes' phase,
# and can't assume that ${DESTDIR}${X11INCDIR} has been populated.
#
SUBDIR=	pswrap makestrs .WAIT

# The rest of the tools can rely upon 'includes'
#
SUBDIR+=bdftopcf fc-cache ucs2any mkg3states
SUBDIR+=makekeys mkfontscale gen_matypes .WAIT xkbcomp

.include <bsd.subdir.mk>
