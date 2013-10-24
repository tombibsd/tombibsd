# $NetBSD$

{
	NF = 2
	print "$0=`" $0 "`"
	print "$3=`" $3 "`"
	print "$4=`" $4 "`"
	NF = 3
	print "$0=`" $0 "`"
	print "$3=`" $3 "`"
	print "$4=`" $4 "`"
	NF = 4
	print "$0=`" $0 "`"
	print "$3=`" $3 "`"
	print "$4=`" $4 "`"
}
