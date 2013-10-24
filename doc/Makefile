#	$NetBSD$

.include <bsd.own.mk>

regen: .PHONY regen-BUILDING
regen-BUILDING: .PHONY
	${TOOL_MANDOC_ASCII} ${.CURDIR}/BUILDING.mdoc \
		| ${TOOL_SED} -e "s,.$$(printf '\b'),,g" \
		>${.CURDIR}/../BUILDING
