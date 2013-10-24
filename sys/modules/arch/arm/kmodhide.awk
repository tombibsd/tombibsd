#	$NetBSD$

substr($NF, 1, 7) == "__wrap_" {
	print " --localize-symbol "$NF;
}
