# $NetBSD$
s/<[^>]*>//g
/&nbsp;&nbsp/ {
	s/&nbsp;/ /g
	s/&#[0-9]*;/ /g
	s/  */ /g
	s/^ *\.//
	s/$//
	p
}
