# $NetBSD$

SUBDIR= lib .WAIT libexec share tests

.for dir in libexec share tests
includes-${dir}: .PHONY
	@true
.endfor

.include <bsd.subdir.mk>
