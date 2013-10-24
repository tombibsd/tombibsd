# $NetBSD$
# utils one might want in a crunched binary

.if !defined(NOTINCRUNCHED)
LDSTATIC=	-static		# only static compilation makes sense here

install: .NOTMAIN .MADE
.endif
